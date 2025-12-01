/**
 * @file webserver.cpp
 * @brief Servidor HTTP simples para interface web
 * @author Arthur Souza Chagas
 * @date 2025
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../include/sistema.h"

#pragma comment(lib, "ws2_32.lib")

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
            std::string value = item.substr(pos + 1);
            params[key] = value;
        }
    }

    return params;
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
            HandleAPI(client, path);
        }
        else {
            SendResponse(client, HTTP_404, CONTENT_TYPE_HTML, "<h1>404</h1>");
        }

        closesocket(client);
    }

    void HandleAPI(SOCKET client, const std::string& path) {
        // API endpoints básicos
        if (path == "/api/feiras") {
            std::string json = "{\"feiras\": []}";  // TODO: implementar
            SendResponse(client, HTTP_200, CONTENT_TYPE_JSON, json);
        }
        else {
            SendResponse(client, HTTP_404, CONTENT_TYPE_JSON, "{\"error\": \"API não encontrada\"}");
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
