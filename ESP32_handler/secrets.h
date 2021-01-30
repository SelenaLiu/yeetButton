#include <pgmspace.h>

#define SECRET
#define THINGNAME "1_ESP32_test"

const char WIFI_SSID[] = "TELUS1283";
const char WIFI_PASSWORD[] = "dt9bncspfx";
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
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJEZKl8e6me+gFOq+Uphf7Lz/GbTMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDEyMTkxODE2
NThaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDOpshJ+v5mkQjpttGk
TQtNCYdRIpMxvfDptztl7gl/zyt9SLOR7uEeMOdI8d5FZqB6p3fCl5X36D+SwAbJ
IBiG8q3GZTyrNGaR/0cMR9fZaDw5fHpS2h12a4FHpBbaLHX1deoN2aYTSOYI942X
wH031yiC9DkT6Rdf6FyPHbRCO+DEmXta+E1Z61Hy2rwGJtQf0W7cMFPksKsvbONQ
UTW1FkYnxSetUEwelh/TOJAlrVEp1COEwTKaYUNhQTgDkVOGqAigs7pdDOyBGfSf
qWd3IgJLtmFlF8HyGGzSRu+/yIn+m9INm1E5f782M1ULxGnfwzIrHcIhYEFLMRHR
IGRTAgMBAAGjYDBeMB8GA1UdIwQYMBaAFP2n8+ZaNvrBXGJ8vwWKO2ylLOyqMB0G
A1UdDgQWBBSvRBTV81wjIOWTcchQV/cwCU+OsjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEASPJxePQYEy+8y3LZLgfpKlyE
QW4ANEHW8O638lYAfgKNENAvNPHSwzm1sI6UFPFa9CvKpzXYCv5Bwv5Tk7tg5GpY
9cAHmzM49iSEZcHAt+djJYcbCmUkzeMRSsWjKBWZr5py857y88BzfTcKhnqKX2SH
xqlOrR97mVyK4UN/fZ3Ne8v6vq6/JaFfidQCf+oIjNDqvpy9/AnT2Zs6c6Icrcv5
CkEVA8XT2B1FU1zjgdV2CeKbusP83exo1aPWS5/oqiWond16bBYTfmwTeSWqnVCd
jfT3jlNvWpp7lSUIHzG2MJ8xd+qErv5ae9H7Qzapo3BB2A/dhJJfBozvmVcXXg==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAzqbISfr+ZpEI6bbRpE0LTQmHUSKTMb3w6bc7Ze4Jf88rfUiz
ke7hHjDnSPHeRWageqd3wpeV9+g/ksAGySAYhvKtxmU8qzRmkf9HDEfX2Wg8OXx6
UtoddmuBR6QW2ix19XXqDdmmE0jmCPeNl8B9N9cogvQ5E+kXX+hcjx20QjvgxJl7
WvhNWetR8tq8BibUH9Fu3DBT5LCrL2zjUFE1tRZGJ8UnrVBMHpYf0ziQJa1RKdQj
hMEymmFDYUE4A5FThqgIoLO6XQzsgRn0n6lndyICS7ZhZRfB8hhs0kbvv8iJ/pvS
DZtROX+/NjNVC8Rp38MyKx3CIWBBSzER0SBkUwIDAQABAoIBAQCOwuOdUDtN6iZJ
J1Ze9ia3eryzzXn4pCp5m276dN61IA8ARyheybNVox005HrUYRi+g1EV6pjdIeJB
ZE2LxpOLLr3kUG4ALHwrojqX/k3c0MjCQf9Tm4E9HPm73102Lf7zqxkdpl239uWM
DlEQJBedaxN+nG+OFLpkNGc1K6UrF2p0Fl6VIug5fE5Xa2bHDEs1MUXWCbgrUOl1
lJ9WpeMw7SZN+WZPpMlVeUSalDxZJfba7lL5FMs3YtorERA9oa1zy0QsZF51H7Ii
4u8786BWZ8wSlid2u5gxxcspHW2+0zfTZOhwCoLSkZCX9l4jERWhlc3olB0vn4op
0wlJj885AoGBAPICVFZu1amHsyGyL2ZmcZsJOmCfl5cDIYcdzOX7ziS9krDma09n
3sSokxWMMErwJpOW/84JM6JuQKtPt+DdxesKcEMHe+/KPcf7oAa8h8VJs76jNONt
NFYE1KbmnFxmxiAn82w0L94kbgHeZDoH8PR0r0K2dZm8J95QTBHOq/0/AoGBANqZ
K3Pqj4X+CZ7QORT1VjTD/SOI6mtOSS/N8S49FEJaVTdXe9NkLgzpwiOmOsZ4fSUl
A/07rtTjc6cu2OUp44X+FpTDkk0UEP3XqtPGsk8wSQ/M1txldqB/rZsOOllgxeWl
5AMv5bySPLNJX6tZxruC4sSlAcfDqRcNNTHgn8/tAoGBAJRZ1TU+r/9CTg7D2cad
2do95+k/K3/IzY60N9xrZUykYP3L4dBFTgujgrZcv2XQnPUwRRMaFOrnRwE81u0j
RaX1Oif8uH6frQugNdKrU1ce/O5JwawAT2rDf0/oYcVKwv0HQHL98rHsBvtiRnJE
V/KibKUqkCBzdMUU1+y6kjelAoGAPC6tSuWKDA7LoUCcZovA5xgKSk04lMBh39po
Cx3fxQDPs0PPoHxVPVLiEySBzACCG8bcGUzkLlJMlfuM1VK6BDrXBq/tSHE82FYW
/uUWVDzr8ICpqtX4Wems5yJ8p/y/nyET7Fi0fD0anxWVVDyMPTWkrxTqr4/LrsAB
JDE+bmUCgYEA5S9V04pm2hX7/Otnj2OYbnD7ggHFuVuTXb1lHTECXemx7evRuxs0
JrJeJD2u7g6PCiZLTTW0yQqSTHrE/sE8X+ll2Xkt8AAdBXWDbzSDS5nVFnwxQVs8
78YaZlmcXKfgIZH44ev+TQu+Omd6Es+MUllOFecUuDnyVZ3kakd1UQ8=
-----END RSA PRIVATE KEY-----
)KEY";