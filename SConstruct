env = Environment(CC = 'g++')

Program(
    "run",

    "test_main.cpp",

    LIBPATH=['third_lib/curlpp/lib', 'third_lib/curl/lib', 'third_lib/c-ares/lib', 'third_lib/cryptopp/lib'],

    LIBS=['curlpp', 'curl', 'cares', 'crypto++', 'pthread', 'z'],

    CPPPATH=['third_lib/curl/include', 'third_lib/curlpp/include', 'third_lib/c-ares/include', 'third_lib/cryptopp/include']
)
