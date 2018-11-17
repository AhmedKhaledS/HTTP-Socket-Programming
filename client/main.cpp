//
// Created by ahmednagga19 on 17/11/18.
//

#include "WebClient.h"

using namespace std;

int main()
{
    WebClient client = WebClient();
    client.send_requests("../requests.txt", "127.0.0.1", 8080, CONNECTION_TYPE::NON_PERSISTENT);
    return 0;
}