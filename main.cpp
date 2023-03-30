#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json.hpp"

#define URL "https://disease.sh/v3/covid-19/"

static size_t WriteCallback(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    ((std::string*)buffer)->append((char*)data, size * nmemb);
    return size * nmemb;
}

void toCapital(std::string &str) {
    if (str.length() == 0) {
        return;
    }
 
    str[0] = std::toupper(str[0]);
}

void printData(char * params)
{
    CURL *curl;
    CURLcode res;
    std::string buffer;

    char url_buffer[256];
    snprintf(url_buffer, sizeof(url_buffer), "%s%s", URL, params);

    // Initialize the curl session
    curl = curl_easy_init();
    if(curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url_buffer);

        // Send all data to this function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Save response body to buffer
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Parse JSON object from buffer if buffer is not empty
    if (!buffer.empty()) {
        nlohmann::json j = nlohmann::json::parse(buffer);
        int updated = j["updated"],
            cases = j["cases"],
            tCases = j["todayCases"],
            deaths = j["deaths"],
            tDeaths = j["todayDeaths"],
            recovered = j["recovered"],
            tRecovered = j["todayRecovered"],
            active = j["active"],
            critical = j["critical"];

        std::cout <<
            "\tUpdated:\t\t" << updated << std::endl;
        
        putchar('\n');

        std::cout <<
            "\tCases:\t\t\t" << cases << std::endl <<
            "\tDeaths:\t\t\t" << deaths << std::endl <<
            "\tRecovered:\t\t" << recovered << std::endl;

        putchar('\n');

        std::cout <<
            "\tCases Today:\t\t" << tCases << std::endl <<
            "\tDeaths Today:\t\t" << tDeaths << std::endl <<
            "\tRecovered Today:\t" << tRecovered << std::endl;

        putchar('\n');

        std::cout <<
            "\tActive:\t\t\t" << active << std::endl <<
            "\tCritical:\t\t" << critical << std::endl;

    } else {
        std::cerr << "Error: buffer is empty" << std::endl;
    } 
}


void title()
{
    system("Color 0A");
    std::cout << "  ___ _____ _  _ ____ ____     ____ ____   __   ___ _  _ ____ ____ \n";
    
    std::cout << " / __(  _  ( \\/ (_  _(  _ \\   (_  _(  _ \\ /__\\ / __( )/ ( ___(  _ \\\n";
    std::cout << "( (__ )(_)( \\  / _)(_ )(_) )    )(  )   //(__)( (__ )  ( )__) )   /\n";
    std::cout << " \\___(_____) \\/ (____(____/    (__)(_)\\_(__)(__\\___(_)\\_(____(_)\\_)" << std::endl;
}

void menu()
{
    std::cout <<
        "\t\tPROGRAMMED BY: YUGEN\n\n" <<
        "\t[1] GLOBAL\n" <<
        "\t[2] CONTINENT\n" <<
        "\t[3] COUNTRY\n\n" <<
        "\t[0] EXIT" << std:: endl;
}

int main()
{
    int c;

    do {
        title();
        menu();

        std::cout << "\tChoice: ";
        std::cin >> c;

        switch (c)
        {
            case 1:
                system("clear");
                title();
                std::cout << "\t\tGLOBAL" << std::endl;
                printData((char*)"all");
                break;
            case 2:
                system("clear");
                title();

                break;
            case 3:
                system("clear");
                title();
                break;
            case 0:
                system("clear");
                title();
                std::cout << "\tExiting..." << std::endl;
                break;
            default:
                system("clear");
                std::cout << "\tInvalid input..." << std::endl;
                break;
        }
    } while (c != 0);

    return 0;
}

