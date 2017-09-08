#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>

class stock
{
private:
	int itm, stk, prc;
	char n[20];
public:
	stock()
	{
		itm = stk = prc = 0;
		strcpy(n, "/0");
	}

	stock(int a, int b, char *c, int d)
	{
		itm = a;
		stk = b;
		strcpy(n, c);
		prc = d;
	}

	void input()
	{
		cout << "enter item number";
		cin >> itm;
		cout << "enter item name";
		cin >> n;
		cout << "enter no. of items in stock";
		cin >> stk;
		cout << "enter the price of the item";
		cin >> prc;
	}


	void show()
	{
		cout << "\n" << itm << "\t" << n << "\t" << stk << "\t" << prc;
	}

	int retitm()
	{
		return itm;
	}
	int retstk()
	{
		return stk;
	}
	char *retn()
	{
		return n;
	}
	int retprc()
	{
		return prc;
	}



	class sales
	{
	private:
		int slno, it, qty, amt;
	public:
		sales()
		{
			slno = it = qty = amt = 0;
		}
		sales(int a, int b, int c, int d)
		{
			slno = a;
			it = b;
			qty = c;
			amt = d;
		}

		void input()
		{
			cout << "enter the item no.";
			cin >> it;
			cout << "enter the quantity";
			cin >> qty;
			cout << "enter the amount";
			cin >> amt;
		}

		void show()
		{
			cout << "\n" << slno << "\t" << qty << "\t" << amt << "\t" << it;
		}
		void recslno(int a)
		{
			slno = a;
		}
		int retslno()
		{
			return slno;
		}
		int retit()
		{
			return it;
		}
		int retqty()
		{
			return qty;
		}
		int retamt()
		{
			return amt;
		}
	};


	//Test the unique slno:
	char search(int p)
	{
		int found = 0;
		fstream a;
		stock m;
		a.open("stock.dat", ios::in | ios::binary);
		if (a != NULL)
		{
			a.read((char *)&m, sizeof(m));
			while (!a.eof())
			{
				if (m.getitm() == p)
				{
					found = 1;
					break;
				}
				a.read((char *)&m, sizeof(m));
			}
			a.close();
		}
		if (found == 0)
			return 'n';
		else
			return 'y';
	}


	//Add a record to stock
	void addstk()
	{
		fstream a;
		stock m;
		a.open("stock.dat", ios::app | ios::binary);
		if (a == NULL)
			cout << "unable to open";
		else
		{
			m.input();
			if (search(m.getitm()) == 1)
				cout << "item no. exit";
			else if (strlen(m.getn())<3)
				cout << "enter a name with atleast 3 character";
			else if (m.getstk()<500)
				cout << "enter atleast 500 stock item";
			else if (m.getprc() <= 1)
				cout << "enter a price more than rs.1";
			else
			{
				a.write((char *)&m, sizeof(m));
				cout << "record inserted";
			}
			a.close();
		}
	}


	//display all records
	void dispitm()
	{
		fstream a;
		stock m;
		int x, k;
		a.open("stock.dat", ios::in | ios::binary);
		if (a == NULL)
			cout << "unable to open";
		else
		{
			cout << "enter a itm no. to search";
			cin >> x;
			if (x>0)
			{
				if (x == m.getitm())
					cout << "\n item no\tname\tstock\tprice";
				while (!a.eof())
				{
					m.show();
					a.read((char *)&m, sizeof(m));
				}
			}
			a.close();
		}
	}


	//delete a record from stock
	void delstk()
	{
		fstream a, b;
		stock m;
		int z, found = 0;
		a.open("stock.dat", ios::in | ios::binary);
		b.open("list.dat", ios::out | ios::binary);
		if (a == NULL || b == NULL)
			cout << "stock empty";
		else
		{
			cout << "\nenter the item no. which we want delete from the list";
			cin >> z;
			a.read((char *)&m, sizeof(m));
			while (!a.eof())
			{
				if (z != m.getitm())
					b.write((char *)&m, sizeof(m));
			}
			if (found == 0)
			{
				unlink("list.dat");
				cout << "item no." << z << "not found\n";
			}
			else
			{
				unlink("stock.dat");
				cout << z << "record deleted";
				z = rename("list.dat", "stock.dat");
			}
			a.close();
			b.close();
		}
	}


	//display all records from stock
	void dispall()
	{
		fstream a;
		stock m;
		a.open("stock.dat", ios::in | ios::binary);
		if (a == NULL)
			cout << "stock empty";
		else
		{
			a.read((char *)&m, sizeof(m));
			if (!a.eof())
				cout << "\n item no\tname\tstock\tprice\n";
			while (!a.eof())
			{
				m.show();
				a.read((char *)&m, sizeof(m));
			}
			a.close();
		}
	}


	//To update a record from stock
	void updstk()
	{
		fstream a;
		stock m;
		int x, found = 0, p, q;
		char n[20];
		a.open("stock.dat", ios::in | ios::out | ios::binary);
		if (a == NULL)
			cout << "enter item no: to search";
		cin >> x;
		a.read((char *)&m, sizeof(m));
		while (!a.eof())
		{
			if (m.getitm() == x)
			{
				found = 1;
				break;
			}
			a.read((char *)&m, sizeof(m));
		}
		if (found == 0)
			cout << "item no: not exist";
		else
		{
			cout << "1.change the item no.\n";
			cout << "2.change name\n";
			cout << "3.change no. of stock\n";
			cout << "4.change price of the item";
			cout << "5.exit\n\n";
			cin >> q;
			switch (q)
			{
			case 1:
				cout << "enter new item no.";
				cin >> p;
				m.recitm(p);
				break;
			case 2:
				cout << "enter new name";
				cin >> n;
				m.recn(n);
				break;
			case 3:
				cout << "enter new stock";
				cin >> p;
				m.recstk(p);
				break;
			case 4:
				cout << "enter new price of thr item";
				cin >> p;
				m.recprc(p);
				break;
			default:
				cout << "\nsorry....wrong choice";
				goto man;
			}
			a.seekg(-(long)sizeof(m), ios::cur);
			a.write((char *)&m, sizeof(m));
			cout << "stock record updated";
		man:
			a.close();
		}
	}


	//generate the slno:
	int slno()
	{
		fstream a;
		sales m;
		int x = 0;
		a.open("sales.dat", ios::in | ios::binary);
		if (a != NULL)
		{
			a.read((char *)&m, sizeof(m));
			x = m.retslno();
			while (!a.eof())
			{
				if (x<m.retslno())
					x = m.retslno();
				a.read((char *)&m, sizeof(m));
			}
			a.close();
		}
		x++;
		return x;
	}

	//Do the sales
	void sales()
	{
		fstream a, b;
		stock p;
		sales q;
		int x = 0;
		a.open("stock.dat", ios::in | ios::out | ios::binary);
		b.open("sales.dat", ios::app | ios::binary);
		if (a == NULL || b == NULL)
			cout << "unable to open";
		else
		{
			q.input();
			q.recslno(slno());
			a.read((char *)&p, sizeof(p));
			while (!a.eof())
			{
				if (q.retit() == p.retit())
				{
					x = 1;
					break;
				}
				a.read((char *)&p, sizeof(p));
			}
			if (x == 0)
				cout << "item does not exist";
			else if ((p.retstk() - q.retqty())<5)
				cout << "p.retstk()-5" << "item available";
			else
			{
				p.recstk(p.retstk() - q.retqty());
				q.recamt(p.retprc()*q.retqty());
				a.seekg(-(long)sizeof(p), ios::cur);
				a.write((char *)&p, sizeof(p));
				b.write((char *)&q, sizeof(q));
				cout << "item sold";
			}
			a.close();
			b.close();
		}
	}


	//to delete the sales
	void delsls()
	{
		fstream a, b;
		sales m;
		int k, f = 0;
		a.open("sales.dat", ios::in | ios::binary);
		b.open("list.dat", ios::out | ios::binary);
		if (a == NULL || b == NULL)
			cout << "sale list empty";
		else
		{
			cout << "enter a slno which we want to delete from the list";
			cin >> k;
			a.read((char *)&m, sizeof(m));
			while (!a.eof())
			{
				if (k != m.getslno())
					b.write((char *)&m, sizeof(m));
				else
					f = 1;
				a.read((char *)&m, sizeof(m));
			}
			a.close();
			b.close();
			if (f == 0)
			{
				unlink("list.dat");
				cout << "slno" << k << "not found";
			}
			else
			{
				unlink("sales.dat");
				k = rename("list.dat", "sales.dat");
				cout << "sales record deleted";
			}
		}
	}


	//display all records from sales
	void displall()
	{
		fstream a;
		sales m;
		a.open("sales.dat", ios::in | ios::binary);
		if (a == NULL)
			cout << "sales empty";
		else
		{
			a.read((char *)&m, sizeof(m));
			if (!a.eof())
				cout << "\n slno\titemno\tqty\tamt\n";
			while (!a.eof())
			{
				m.show();
				a.read((char *)&m, sizeof(m));
			}
			a.close();
		}
	}


	//To update a record from sales
	void updsls()
	{
		fstream a;
		sales m;
		int x, found = 0, p, q;
		char n[20];
		a.open("sales.dat", ios::in | ios::out | ios::binary);
		if (a == NULL)
			cout << "enter slno: to search";
		cin >> x;
		a.read((char *)&m, sizeof(m));
		while (!a.eof())
		{
			if (m.getitm() == x)
			{
				found = 1;
				break;
			}
			a.read((char *)&m, sizeof(m));
		}
		if (found == 0)
			cout << "slno: not exist";
		else
		{
			cout << "1.change the slno:\n";
			cout << "2.change item no:\n";
			cout << "3.change the quantiy\n";
			cout << "4.change amount of the item";
			cout << "5.exit\n\n";
			cin >> q;
			switch (q)
			{
			case 1:
				cout << "enter new slno:";
				cin >> p;
				m.recitm(p);
				break;
			case 2:
				cout << "enter item no:";
				cin >> n;
				m.recn(n);
				break;
			case 3:
				cout << "enter the quantity";
				cin >> p;
				m.recstk(p);
				break;
			case 4:
				cout << "enter new amount of the item";
				cin >> p;
				m.recprc(p);
				break;
			default:
				cout << "\nsorry....wrong choice";
				goto woman;
			}
			a.seekg(-(long)sizeof(m), ios::cur);
			a.write((char *)&m, sizeof(m));
			cout << "sales record updated";
		woman:
			a.close();
		}
	}


	void main()
	{
		int ch;
		do
		{
			clrscr();
			cout << "1.Add a record to stock\n2.display all records\n3.delete a record from stock\n4.display all records from stock\n5.update a record from stock\n6.Do the sales\n7.delete the sales\n8.display all records from sales\n9.update a record from sales\n10.exit\n\n\n";
			cout << "enter your choice:";
			cin >> ch;
			switch (ch)
			{
			case 1: addstk(); break;
			case 2: dispitm(); break;
			case 3: delstk(); break;
			case 4: dispall(); break;
			case 5: updstk(); break;
			case 6: sales(); break;
			case 7: delsls(); break;
			case 8: displall(); break;
			case 9: updsls(); break;
			}
			getch();
		} while (ch != 10);
	}


