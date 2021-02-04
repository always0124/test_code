// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include "base64.h"
#include <string>
using std::string;
#include "modes.h"
#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "aes.h"
using CryptoPP::AES;

#include "ccm.h"
using CryptoPP::CBC_Mode;

#include "assert.h"

int main(int argc, char* argv[])
{
	AutoSeededRandomPool prng;

	byte key[AES::DEFAULT_KEYLENGTH];
    std::cout << sizeof(byte) << "\t" << sizeof(key) << std::endl;
	//prng.GenerateBlock(key, sizeof(key));
    memset(key,0,sizeof(key));
	byte iv[AES::BLOCKSIZE];

    std::cout << sizeof(byte) << "\t" << sizeof(iv) << std::endl;
    //prng.GenerateBlock(iv, sizeof(iv));
    memset(iv,0,sizeof(iv));
	string plain = "dinghui";
      
    /*  FILE* fP = fopen("test.txt","r");
    if(NULL == fP) {return 0;}
    char buf[1024 * 1024];
    std::string plain;
    while(NULL != fgets(buf,sizeof(buf),fP)) {
        plain.append(buf);
    }*/


	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new CryptoPP::Base64Encoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,
		new CryptoPP::Base64Encoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "iv: " << encoded << endl;

	/*********************************\
	\*********************************/

    while(cin >> plain) {
	
        recovered.clear();
        try
	{

		cout << "plain text: " << plain << endl;

		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		cipher.clear();
        StringSource (plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher) ,CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
			) // StreamTransformationFilter
		); // StringSource
        
        encoded.clear();
	    StringSource (cipher,true,
                new CryptoPP::Base64Encoder(new StringSink(encoded))); // StringSource
	    cout << "PKCS_PADDING cipher text: " << encoded << endl;
    
        /*  cipher.clear();
        StringSource (plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher),CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING
			) // StreamTransformationFilter
		); // StringSource
        
        encoded.clear();
	    StringSource (cipher,true,
                new CryptoPP::Base64Encoder(new StringSink(encoded))); // StringSource
	    cout << "DEFAULT_PADDING cipher text: " << encoded << endl;

        cipher.clear();
        StringSource (plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher),CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
			) // StreamTransformationFilter
		); // StringSource
        
        encoded.clear();
	    StringSource (cipher,true,
                new CryptoPP::Base64Encoder(new StringSink(encoded))); // StringSource
	    cout << "PKCS_PADDING cipher text: " << encoded << endl;

        cipher.clear();
        StringSource (plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher),CryptoPP::BlockPaddingSchemeDef::ONE_AND_ZEROS_PADDING
			) // StreamTransformationFilter
		); // StringSource
        
        encoded.clear();
	    StringSource (cipher,true,
                new CryptoPP::Base64Encoder(new StringSink(encoded))); // StringSource
	    cout << "ONE_AND_ZEROS_PADDING cipher text: " << encoded << endl;
        */

#if 0
		StreamTransformationFilter filter(e);
		filter.Put((const byte*)plain.data(), plain.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		cipher.resize(ret);
		filter.Get((byte*)cipher.data(), cipher.size());
#endif
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

    FILE* f = fopen("out.data","wb");
    fwrite(cipher.c_str(),cipher.size(),1,f);
    fclose(f);

	// Pretty print
	encoded.clear();
	StringSource s(cipher,true,
		 new CryptoPP::Base64Encoder(new StringSink(encoded))); // StringSource
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv);
        /*std::string str = "34+kGe9WO6TqO+ayZjQ2Jw==";*/
        std::string str = "u7KifL5mobX3ORnlet91OQ==";
        std::cout << cipher.size() << std::endl;
        cipher.clear();
        StringSource (str,true,new CryptoPP::Base64Decoder(new StringSink(cipher)));
        
        
        std::cout <<cipher.size() << std::endl;
        
		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true, 
			new StreamTransformationFilter(d,
				new StringSink(recovered) ,CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING
			) // StreamTransformationFilter
		); // StringSource
        /*  CBC_Decryption cbc;
        cbc.SetKeyWithIV(key,sizeof(key),iv);
        byte decry[256];
        cbc.processData(decry,bak_cipher.c_str(),bak_cipher.size());
        */
#if 0
		StreamTransformationFilter filter(d);
		filter.Put((const byte*)cipher.data(), cipher.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		recovered.resize(ret);
		filter.Get((byte*)recovered.data(), recovered.size());
#endif

		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    }
	/*********************************\
	\*********************************/

	return 0;
}

