#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sqlite_modern_cpp.h>

using namespace  sqlite;
using namespace std;

struct TmpFile {
	string fname;

	TmpFile() {
		char f[] = "/tmp/sqlite_modern_cpp_test_XXXXXX";
		int fid = mkstemp(f);
		close(fid);

		fname = f;
	}

	~TmpFile() {
		unlink(fname.c_str());
	}
};

int main() {
	try {

		TmpFile file;
		database db(file.fname);

		{

			auto con = db.connection();

			{
				database db2(con);
				int test = 0;
				db2 << "select 1" >> test;
				if(test != 1) exit(EXIT_FAILURE);
			}

			int test = 0;
			db << "select 1" >> test;
			if(test != 1) exit(EXIT_FAILURE);

		}


	} catch(sqlite_exception e) {
		cout << "Unexpected error " << e.what() << endl;
		exit(EXIT_FAILURE);
	} catch(...) {
		cout << "Unknown error\n";
		exit(EXIT_FAILURE);
	}

	cout << "OK\n";
	exit(EXIT_SUCCESS);
}
