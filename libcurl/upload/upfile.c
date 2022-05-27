#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <curl/curl.h>

int main(void)
{
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curl_formadd(&formpost,
                    &lastptr,
                    CURLFORM_COPYNAME, "file",
                    CURLFORM_FILE, "/home/cjb/share/githup_prj/tech-note/c/libcurl/upload/hello.txt",
                    CURLFORM_END);
    curl_formadd(&formpost,  
               &lastptr,  
               CURLFORM_COPYNAME, "filename",  
               CURLFORM_COPYCONTENTS, "hello.txt",  
               CURLFORM_END);
    curl_formadd(&formpost,  
               &lastptr,  
               CURLFORM_COPYNAME, "submit",  
               CURLFORM_COPYCONTENTS, "upload",  
               CURLFORM_END);
    curl_formadd(&formpost,  
               &lastptr,  
               CURLFORM_COPYNAME, "output",  
               CURLFORM_COPYCONTENTS, "json2",  
               CURLFORM_END);
    headerlist = curl_slist_append(headerlist, buf);
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.128.94:21013/upload");
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                        curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(headerlist);
    }
    return 0;
}