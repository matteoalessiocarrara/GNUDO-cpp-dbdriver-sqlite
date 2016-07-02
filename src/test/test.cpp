/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# include <iostream>
# include <vector>

# include "../gnudo.hpp"


using namespace gnudo::sqlite;
using std::vector;
using std::cout;
using std::endl;


int main()
{	
	Db db("test.db");
	
	sqlite3_int64 id = db.getTasks()->add("Prova", "123 123");
	Task* t = db.getTasks()->getTask(id);

	t->setTitle("Questo task non esiste");
	t->setDescription("Niente qui");
	t->setStatus(true);

	vector<sqlite3_int64> l = db.getTasks()->getIdList();
	
	for(vector<sqlite3_int64>::iterator i = l.begin(); i != l.end(); i++)
	{
		gnudo::sqlite::Task *t2 = db.getTasks()->getTask(*i);

		cout << "**************************************************************" << endl;
		cout << "Id: " << t2->getId() << endl;
		cout << "Title: " << t2->getTitle() << endl;
		cout << "Description: " << t2->getDescription() << endl;
		cout << "Creation time: " << t2->getCreationTime() << endl;
		cout << "Modification time: " << t2->getModificationTime() << endl;
		cout << "Is completed: "<< t2->isCompleted() << endl;

		delete t2;
	}


	db.getTasks()->remove(t);

	return 0;
}
