sed \
    -e 's/^-----BEGIN CERTIFICATE-----$/4e32566d-8e9e-4f52-81d3-5bb9715f9727:/' \
    -e '/^-----END CERTIFICATE-----$/d' \
    ./PkKek1.pem > PkKek1.oemstr
