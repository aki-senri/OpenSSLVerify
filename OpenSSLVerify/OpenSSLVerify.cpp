#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/core_names.h"
#include "openssl/bn.h"

int main()
{
	std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary;
	std::ifstream public_key_n_stream("public_n.dat", mode);
	std::ifstream public_key_e_stream("public_e.dat", mode);

	std::vector<std::uint8_t> n_bin;
	std::vector<std::uint8_t> e_bin;

	while (public_key_n_stream.good())
	{
		n_bin.push_back(public_key_n_stream.get());
	}

	while (public_key_e_stream.good())
	{
		e_bin.push_back(public_key_e_stream.get());
	}

	auto public_key = EVP_PKEY_new();
	BIGNUM* n = BN_new();
	BIGNUM* e = BN_new();

	EVP_PKEY_set_bn_param(public_key, OSSL_PKEY_PARAM_RSA_N, n);
	EVP_PKEY_set_bn_param(public_key, OSSL_PKEY_PARAM_RSA_E, e);

	BN_free(n);
	BN_free(e);
}
