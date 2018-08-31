echo -e "[+] Installing dependencies...\n"

sudo apt-get install libxml2 libxml2-dev libcurl4 libcurl4-gnutls-dev

echo -ne "\n[+] Compiling..."

gcc -o simple-get simple-get.c sg_lib.c \
  $(pkg-config --cflags --libs libxml-2.0 libcurl) \
  $(xml2-config --cflags --libs)

echo "DONE."
