#include <crypto++/files.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/rsa.h>
#include <crypto++/sha.h>
#include <crypto++/base64.h>
#include <sys/time.h>
void rsa_examples()
{
    // Keys created here may be used by OpenSSL.
    //
    // openssl pkcs8 -in key.der -inform DER -out key.pem -nocrypt 
    // openssl rsa -in key.pem -check

    CryptoPP::AutoSeededRandomPool rng;

    // Create a private RSA key and write it to a file using DER.
    CryptoPP::RSAES_OAEP_SHA_Decryptor priv( rng, 4096 );
    CryptoPP::TransparentFilter privFile( new CryptoPP::FileSink("rsakey.der") );
    priv.DEREncode( privFile );
    privFile.MessageEnd();

    // Create a private RSA key and write it to a string using DER (also write to a file to check it with OpenSSL).
    std::string the_key;
    CryptoPP::RSAES_OAEP_SHA_Decryptor pri( rng, 2048 );
    CryptoPP::TransparentFilter privSink( new CryptoPP::StringSink(the_key) );
    pri.DEREncode( privSink );
    privSink.MessageEnd();

    std::ofstream file ( "key.der", std::ios::out | std::ios::binary );
    file.write( the_key.data(), the_key.size() );
    file.close();

    // Example Encryption & Decryption
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize( rng, 1536 );
    
    FILE* fP = fopen("test.txt","r");
    if(NULL == fP) {return;}
    char buf[1024 * 1024];
    std::string plain;
    while(NULL != fgets(buf,sizeof(buf),fP)) {
        plain.append(buf);
    }

    timeval start,end;
    gettimeofday(&start,NULL);

    for(int i = 0; i < 1000; ++ i) {

        std::string  cipher, decrypted_data;

        CryptoPP::RSA::PrivateKey privateKey( params );
        CryptoPP::RSA::PublicKey publicKey( params );

        CryptoPP::RSAES_OAEP_SHA_Encryptor e( publicKey );
        CryptoPP::StringSource( plain, true, new CryptoPP::PK_EncryptorFilter( rng, e, new CryptoPP::StringSink( cipher )));
        //std::cout << cipher.length() << std::endl;


        CryptoPP::RSAES_OAEP_SHA_Decryptor d( privateKey );
        CryptoPP::StringSource( cipher, true, new CryptoPP::PK_DecryptorFilter( rng, d, new CryptoPP::StringSink( decrypted_data )));

        //std::cout << plain << "\t" << decrypted_data << std::endl;

        assert( plain == decrypted_data );
    }
    gettimeofday(&end,NULL);
    std::cout << 1000000 *(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) << std::endl;

}
int main()
{
    rsa_examples();
    return 0;
}
