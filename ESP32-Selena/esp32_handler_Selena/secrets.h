#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32-Selena"

const char WIFI_SSID[] = "SHAW-6C17B0";
const char WIFI_PASSWORD[] = "2511690B6637";
const char AWS_IOT_ENDPOINT[] = "a2cdegumelepxp-ats.iot.us-east-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
------BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOVfjf3t4R/yt9eL7FtM7nWRQhP8MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDEyMjMxODUy
NTZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCq+BZdRFEVU9O0vqku
NQChXFS7Pnhun5uMNRlio3oeqpL2PDGrWf/HVKR2Gj3p/YLTT1mdhUADyPZLrohf
LgrMISC6gwm95UF07/oRvN9nd9vztxE1fvXeu5ImxoZUKWb7zgVNEqGU/MlQmt/f
Bv928/+3cRujf6/+9fKGj9JHfhWX2GTEpXMg0eRJgcLERbXg2ALIqH7VnOWPSUwq
UHTi1megbL7B5D2viDFGbXmdw9TvmOjMIj0KuUUIBA1XK5lSifupe253CrVUmv2f
ZsTfichaH1MhGrVboKNdyXeDKG77zqvzx5+Gjd85grGLKQaf+e8nqu/rNOWYiVPr
ufd3AgMBAAGjYDBeMB8GA1UdIwQYMBaAFIcU5kPxpp3Tw4AaXUBIJEj7HlFvMB0G
A1UdDgQWBBT6pqsaeuP8YkYomIraS7stGRHB/TAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAFdxkyNEAAyqZtnUBiOM94Xa0
L5iUWQd9s/W5IqPioklGKJ+11kPOdaydUa4aRhL/HzJleitngtRE3k7R4PM++RnN
VjYtMayeWpYLy9PcMiJl80AFnFwVDLRLQQSaHg4tEQckAUM5cdDkjW+WVaHtRLWH
LlDAYcbEc5/DOUMmxkUjA1iF27bQ/coLJX78Nnheo/M/bWye5W7aptA73ezSu+/0
mCwPU98rIuHyIZob8xecChcbLr9+edXXMNv8qhG7BbG8ay1BCbCK5lxB9+2eEUNW
ktJSk0H8LKp3lOLKI1I5dYLG5DqXNhrnPxFHSz+YQp8I7E6Y1MKvqQMsTWy0rw==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAqvgWXURRFVPTtL6pLjUAoVxUuz54bp+bjDUZYqN6HqqS9jwx
q1n/x1Skdho96f2C009ZnYVAA8j2S66IXy4KzCEguoMJveVBdO/6EbzfZ3fb87cR
NX713ruSJsaGVClm+84FTRKhlPzJUJrf3wb/dvP/t3Ebo3+v/vXyho/SR34Vl9hk
xKVzINHkSYHCxEW14NgCyKh+1Zzlj0lMKlB04tZnoGy+weQ9r4gxRm15ncPU75jo
zCI9CrlFCAQNVyuZUon7qXtudwq1VJr9n2bE34nIWh9TIRq1W6CjXcl3gyhu+86r
88efho3fOYKxiykGn/nvJ6rv6zTlmIlT67n3dwIDAQABAoIBAGIXXrV6Oc8zvjZo
YaaqMEdkMxUPHYfSuSrzWDI4uxsXIKR4GsNGKrNRw94i5jz2/3V/hFoVFopVZcI8
S+/X+cfuhdmczx0NiMWv3dkJdV/m6+JjuVLpGeYF1i+7HVzyOCzmojH7K4vQkSxW
/3T1jeLQ0XmNQp9G5lIxCEneAHaVV3fnSk1FN837UhrZadoMKgWnhsQ/5a775LVC
GNhgzl3JruLrfwuoNe15V6mNuViNoTXcBqf9j0AggrUDugYHrU4GmnVxxM/xeEHr
6vjhADpyIP0KS7Sx3wxoFoHTiHVDdqDyLztmukwqytWZc9u0hoYdKSb8xgwvo1d9
GYkU01kCgYEA04pySDsa/TB0poMUDaYugDF9MS2TZDrxoKN6FcS+ALzqZ20QVG4l
+7/E1Bgq0Wdk0mDaL+FaEbmyP/er+NrRRXFFxRNMsuQektsxWsQB2ELo6iAtKBEk
9ut+ezrDlRB4OQ+uCaa+gFYf/7XibFUSczfVu+wf9pXEsu6Ky3gj/NMCgYEAzubB
pee1y5Kelkn++Nf6duc4XaJc4nTptCXU0mSNnxyIaSda9WZa/PaqOglsuDlDzHgJ
oYDPDQBLvoMp4OFZgiUCjOb+8Xv2eaN+ZT415D+HY2qjIA9l0UuSX0xpGbSul0rV
JhlxQB8tIDmD847TSZtiDw1XkGPy70Y6k1R55E0CgYEAu09FriuX1EUJpT8/jG5v
klc/0UHX1tJSjbjzKz9QNnsQ24+4++mkfGvrrxnPICh7H8VerTLPfA5/hSCbB/lJ
gEGyU7SpH2XapJKt+v6/22wzrMvc8DNuFa2kCx2XfPBeY7g8lJMu75hTMSsuWFpj
wd3YxVNpYgBvcTjDcTLqOr0CgYB91RXdAskr4CYXHTW2vhQUEJfVSpPXHmesKn3+
3yzKoh3MZiUJrpCT3Ki211iJyjoTtsWUtbQ3IgDvAvKLVEKNxliAvVQ8JbpHTEno
5Sb9hC2hJw/CxdqUqbOBxgT9n0e3t8lefIbGCq/1M0Wu8SRLVfcTVHf21vK+1yV0
ySHA2QKBgEdWznRr//8z+v/FEyzSFVj40J1XYQv+RvQu/zuzOzal5slSLzE4AflH
PC1C7v777seM5ayyxUoPjJXEd0eeM1IcM4jZWaBktX+52vQ4vrMc5MabVFUpGKPa
TCWgNUtCKiyEnqbdde2R+C4+uwBjcVKsitt6n8m22zbJmxEeJT0c
-----END RSA PRIVATE KEY-----
)KEY";
