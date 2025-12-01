/**
 * @file webserver.cpp
 * @brief Servidor HTTP com API REST integrada ao backend C++
 * @author Arthur Souza Chagas
 * @date 2025
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../include/sistema.h"

#pragma comment(lib, "ws2_32.lib")

// Protótipos das funções do database.cpp
void InicializarBancoDeDados(Sistema* sistema);
std::string SistemaParaJSON(Sistema* sistema);
std::string EscapeJSON(const std::string& s);

// Códigos de resposta HTTP
const std::string HTTP_200 = "HTTP/1.1 200 OK\r\n";
const std::string HTTP_404 = "HTTP/1.1 404 Not Found\r\n";
const std::string HTTP_500 = "HTTP/1.1 500 Internal Server Error\r\n";

// Headers comuns
const std::string CONTENT_TYPE_HTML = "Content-Type: text/html; charset=utf-8\r\n";
const std::string CONTENT_TYPE_JSON = "Content-Type: application/json; charset=utf-8\r\n";
const std::string CONTENT_TYPE_CSS = "Content-Type: text/css; charset=utf-8\r\n";
const std::string CONTENT_TYPE_JS = "Content-Type: application/javascript; charset=utf-8\r\n";
const std::string CORS_HEADERS = "Access-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: GET, POST, OPTIONS\r\n";

/**
 * @brief Lê arquivo e retorna conteúdo
 */
std::string ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return "";

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Envia resposta HTTP
 */
void SendResponse(SOCKET client, const std::string& status,
                  const std::string& contentType, const std::string& body) {
    std::stringstream response;
    response << status;
    response << contentType;
    response << CORS_HEADERS;
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << body;

    std::string resp = response.str();
    send(client, resp.c_str(), resp.length(), 0);
}

/**
 * @brief Decodifica URL encoding
 */
std::string URLDecode(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '+') {
            result += ' ';
        } else if (str[i] == '%' && i + 2 < str.length()) {
            int value;
            std::istringstream is(str.substr(i + 1, 2));
            if (is >> std::hex >> value) {
                result += static_cast<char>(value);
                i += 2;
            }
        } else {
            result += str[i];
        }
    }
    return result;
}

/**
 * @brief Parse URL parameters
 */
std::map<std::string, std::string> ParseQuery(const std::string& query) {
    std::map<std::string, std::string> params;
    std::stringstream ss(query);
    std::string item;

    while (std::getline(ss, item, '&')) {
        size_t pos = item.find('=');
        if (pos != std::string::npos) {
            std::string key = item.substr(0, pos);
            std::string value = URLDecode(item.substr(pos + 1));
            params[key] = value;
        }
    }

    return params;
}

/**
 * @brief Converte string para minúscula
 */
std::string ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

/**
 * @brief Servidor HTTP principal
 */
class WebServer {
private:
    SOCKET serverSocket;
    int port;
    Sistema* sistema;

public:
    WebServer(int p) : port(p), sistema(new Sistema()) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        // Inicializar banco de dados
        InicializarBancoDeDados(sistema);
    }

    ~WebServer() {
        closesocket(serverSocket);
        WSACleanup();
        delete sistema;
    }

    bool Start() {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Erro ao criar socket\n";
            return false;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Erro ao fazer bind na porta " << port << "\n";
            return false;
        }

        if (listen(serverSocket, 10) == SOCKET_ERROR) {
            std::cerr << "Erro ao escutar conexões\n";
            return false;
        }

        std::cout << "🌐 Servidor iniciado em http://localhost:" << port << "\n";
        std::cout << "📊 Backend C++ integrado com " << sistema->GetFeiras().size() << " feiras\n";
        std::cout << "📱 Abra seu navegador e acesse a URL acima\n";
        std::cout << "🛑 Pressione Ctrl+C para parar\n\n";

        return true;
    }

    void HandleClient(SOCKET client) {
        char buffer[4096] = {0};
        recv(client, buffer, sizeof(buffer), 0);

        std::string request(buffer);
        std::string method, path, version;
        std::istringstream iss(request);
        iss >> method >> path >> version;

        std::cout << method << " " << path << "\n";

        // Extrair query string
        std::string query = "";
        size_t qpos = path.find('?');
        if (qpos != std::string::npos) {
            query = path.substr(qpos + 1);
            path = path.substr(0, qpos);
        }

        // Roteamento
        if (path == "/" || path == "/index.html") {
            std::string html = ReadFile("web/index.html");
            if (!html.empty()) {
                SendResponse(client, HTTP_200, CONTENT_TYPE_HTML, html);
            } else {
                SendResponse(client, HTTP_404, CONTENT_TYPE_HTML, "<h1>404 - Página não encontrada</h1>");
            }
        }
        else if (path == "/style.css") {
            std::string css = ReadFile("web/style.css");
            SendResponse(client, HTTP_200, CONTENT_TYPE_CSS, css);
        }
        else if (path == "/app.js") {
            std::string js = ReadFile("web/app.js");
            SendResponse(client, HTTP_200, CONTENT_TYPE_JS, js);
        }
        else if (path.find("/api/") == 0) {
            HandleAPI(client, path, query);
        }
        else {
            SendResponse(client, HTTP_404, CONTENT_TYPE_HTML, "<h1>404</h1>");
        }

        closesocket(client);
    }

    void HandleAPI(SOCKET client, const std::string& path, const std::string& query) {
        // GET /api/feiras - Lista todas as feiras
        if (path == "/api/feiras") {
            std::string json = SistemaParaJSON(sistema);
            SendResponse(client, HTTP_200, CONTENT_TYPE_JSON, json);
        }
        // GET /api/produtos - Lista todos os produtos
        else if (path == "/api/produtos") {
            std::ostringstream json;
            json << "{\n  \"produtos\": [\n";

            const auto& feiras = sistema->GetFeiras();
            bool first_product = true;

            for (const auto& feira : feiras) {
                for (const auto& produto : feira.GetProdutos()) {
                    if (!first_product) json << ",\n";
                    first_product = false;

                    json << "    {\n";
                    json << "      \"nome\": \"" << EscapeJSON(produto.GetNome()) << "\",\n";
                    json << "      \"preco\": " << produto.GetPreco() << ",\n";
                    json << "      \"categoria\": \"" << EscapeJSON(produto.GetCategoria()) << "\",\n";
                    json << "      \"feira\": \"" << EscapeJSON(feira.GetNome()) << "\",\n";
                    json << "      \"feiraRA\": \"" << EscapeJSON(feira.GetEndereco()) << "\"\n";
                    json << "    }";
                }
            }

            json << "\n  ]\n}\n";
            SendResponse(client, HTTP_200, CONTENT_TYPE_JSON, json.str());
        }
        // GET /api/buscar?termo=tomate - Busca produtos
        else if (path == "/api/buscar") {
            auto params = ParseQuery(query);
            std::string termo = ToLower(params["termo"]);

            std::ostringstream json;
            json << "{\n  \"resultados\": [\n";

            const auto& feiras = sistema->GetFeiras();
            bool first = true;

            for (const auto& feira : feiras) {
                for (const auto& produto : feira.GetProdutos()) {
                    std::string nome_lower = ToLower(produto.GetNome());
                    if (nome_lower.find(termo) != std::string::npos) {
                        if (!first) json << ",\n";
                        first = false;

                        json << "    {\n";
                        json << "      \"nome\": \"" << EscapeJSON(produto.GetNome()) << "\",\n";
                        json << "      \"preco\": " << produto.GetPreco() << ",\n";
                        json << "      \"categoria\": \"" << EscapeJSON(produto.GetCategoria()) << "\",\n";
                        json << "      \"feira\": \"" << EscapeJSON(feira.GetNome()) << "\",\n";
                        json << "      \"feiraRA\": \"" << EscapeJSON(feira.GetEndereco()) << "\"\n";
                        json << "    }";
                    }
                }
            }

            json << "\n  ]\n}\n";
            SendResponse(client, HTTP_200, CONTENT_TYPE_JSON, json.str());
        }
        // GET /api/filtrar?categoria=Hortifruti&precoMax=5.00&ra=Ceilandia
        else if (path == "/api/filtrar") {
            auto params = ParseQuery(query);
            std::string categoria = params["categoria"];
            double precoMax = params["precoMax"].empty() ? 999999.0 : std::stod(params["precoMax"]);
            std::string ra = params["ra"];

            std::ostringstream json;
            json << "{\n  \"resultados\": [\n";

            const auto& feiras = sistema->GetFeiras();
            bool first = true;

            for (const auto& feira : feiras) {
                // Filtrar por RA (se especificado)
                if (!ra.empty() && feira.GetEndereco().find(ra) == std::string::npos) {
                    continue;
                }

                for (const auto& produto : feira.GetProdutos()) {
                    // Filtrar por categoria
                    if (!categoria.empty() && produto.GetCategoria() != categoria) {
                        continue;
                    }

                    // Filtrar por preço
                    if (produto.GetPreco() > precoMax) {
                        continue;
                    }

                    if (!first) json << ",\n";
                    first = false;

                    json << "    {\n";
                    json << "      \"nome\": \"" << EscapeJSON(produto.GetNome()) << "\",\n";
                    json << "      \"preco\": " << produto.GetPreco() << ",\n";
                    json << "      \"categoria\": \"" << EscapeJSON(produto.GetCategoria()) << "\",\n";
                    json << "      \"feira\": \"" << EscapeJSON(feira.GetNome()) << "\",\n";
                    json << "      \"feiraRA\": \"" << EscapeJSON(feira.GetEndereco()) << "\"\n";
                    json << "    }";
                }
            }

            json << "\n  ]\n}\n";
            SendResponse(client, HTTP_200, CONTENT_TYPE_JSON, json.str());
        }
        else {
            SendResponse(client, HTTP_404, CONTENT_TYPE_JSON, "{\"error\": \"Endpoint não encontrado\"}");
        }
    }

    void Run() {
        while (true) {
            sockaddr_in clientAddr;
            int clientSize = sizeof(clientAddr);
            SOCKET client = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

            if (client != INVALID_SOCKET) {
                HandleClient(client);
            }
        }
    }
};

int main() {
    WebServer server(8080);

    if (server.Start()) {
        server.Run();
    }

    return 0;
}
