#include<iostream>
#include<stack>
#include<string>
#include<vector>

/*
 * 我需要getch函数，但linux没有，所以需要自己实现
 * 这边判断是windows还是linux
 * 如果是linux就用自己实现的getch
 * 如果是windows就用conio里面的getch
 */
#ifdef __linux__
#include<unistd.h>
#include<termio.h>
int getch();

#elif _WIN32
#include<conio.h>

#endif

using namespace std;
int nav = 1;

struct Product 
{
    string name;
    string category;
    string label;
    int quantity;
    double price;
    Product(string& n, string& c, string& l, int q, double p):name(n), category(c), label(l), quantity(q), price(p) {}
};

//用栈将库存保存起来（非常的形象生动）
stack<Product> inventory;
//添加产品函数
void addProduct(string& name, string& category, string& label, int quantity, double price) 
{
	inventory.push(Product(name, category, label, quantity, price));
    cout<<"添加了: "<<name<<endl;
	getchar();
	getchar();
}
	//删除产品函数
void removeProduct(string& name) 
{
	bool flag = false;
    stack<Product> temp;//遍历栈需要pop, 所以防止数据丢失建立temp栈保存
    while(!inventory.empty()) 
	{
       	Product product = inventory.top();
        inventory.pop();
        if(product.name != name) temp.push(product);
		else cout<<"已删除: "<<name<<endl, flag = true;
    }
    while(!temp.empty()) //将数据放回原栈
	{
    	inventory.push(temp.top());
        temp.pop();
    }
	if(flag) getchar(), getchar();
}
//显示库存函数
void displayInventory() 
{
	cout<<"当前库存:"<<endl;
	if(inventory.empty())cout<<"-----------\n";
	else cout<<"==\n";

    stack<Product> temp;//建立temp栈保存数据
    while(!inventory.empty()) 
	{
    	Product product = inventory.top();
        inventory.pop();
        cout<<"名字: "<<product.name<<", 类别: "<<product.category
            <<", 标签: "<<product.label<<", 数量: "<<product.quantity
            <<", 价格: "<<product.price<<endl;
        temp.push(product);
    }
    while(!temp.empty()) //放回原栈中
	{
    	inventory.push(temp.top());
        temp.pop();
    }
	if(!inventory.empty()) cout<<"==\n";
}
//购买产品到库函数
void purchaseProduct(string& name, int quantity) 
{
	stack<Product> temp;
    while(!inventory.empty()) 
	{
        Product product = inventory.top();
        inventory.pop();
        if(product.name == name) 
		{
        	product.quantity += quantity;
            temp.push(product);
            cout<<"购买了"<<quantity<<"个"<<name<<endl;
        } else temp.push(product); 
     }
    while(!temp.empty()) 
	{
    	inventory.push(temp.top());
        temp.pop();
    }
	getchar();
	getchar();
}
	//产品售出函数
void sellProduct(string& name, int quantity) 
{
	stack<Product> temp;
	while(!inventory.empty()) 
	{
		Product product = inventory.top();
		inventory.pop();
		if(product.name == name) 
		{
			if(product.quantity < quantity) 
			{
				cout<<name<<" 数量不足!"<<endl;
				temp.push(product);
				break;
			}
			product.quantity -= quantity;
			temp.push(product);
			cout<<"已出售"<<quantity<<"个"<<name<<endl;
		} else temp.push(product);
	}
	while(!temp.empty()) 
	{
		inventory.push(temp.top());
		temp.pop();
	}
	getchar();
	getchar();
}
	//更新价格函数
void updatePrice(string& name, double price) 
{
	stack<Product> temp;
	while(!inventory.empty()) 
	{
		Product product = inventory.top();
		inventory.pop();
		if(product.name == name) 
		{
			product.price = price;
			temp.push(product);
			cout<<name<<" 的价格已改为"<<price<<endl;
		}else temp.push(product);
	}
	while(!temp.empty()) 
	{
		inventory.push(temp.top());
		temp.pop();
	}
	getchar();
	getchar();
}
void exportInventory(const string& filename) 
{
	FILE* file = fopen(filename.c_str(), "w");
	if(file == nullptr) 
	{
		cout<<"程序错误,无法保存"<<endl;
		return;
	}
	stack<Product> temp;
	while(!inventory.empty()) 
	{
		Product product = inventory.top();
		inventory.pop();
		fprintf(file, "%s,%s,%s,%d,%.2f\n", product.name.c_str(), product.category.c_str(), product.label.c_str(), product.quantity, product.price);
		temp.push(product);
	}
	while(!temp.empty()) 
	{
		inventory.push(temp.top());
		temp.pop();
	}
	fclose(file);
	cout<<"已导出为"<<filename<<endl;
	sleep(1);
}
void importInventory(const string& filename) 
{
	FILE* file = fopen(filename.c_str(), "r");
	if(file == nullptr) return;

	char name[100], category[100], label[100];
	string sname, scategory, slabel;
	int quantity;
	double price;

	while(fscanf(file, "%[^,],%[^,],%[^,],%d,%lf\n", name, category, label, &quantity, &price) != EOF) 
	{
		sname = name; scategory = category; slabel = label;
		inventory.push(Product(sname, scategory, slabel, quantity, price));
	}
	fclose(file);
}
//打印主菜单
void printMenu() 
{
    cout<<"====超市进销管理系统===="<<endl;
	cout<<"      "<<(nav==1?"*":" ")<<"添加产品"<<endl;
    cout<<"      "<<(nav==2?"*":" ")<<"删除产品"<<endl;
    cout<<"      "<<(nav==3?"*":" ")<<"购买产品"<<endl;
    cout<<"      "<<(nav==4?"*":" ")<<"售出产品"<<endl;
    cout<<"      "<<(nav==5?"*":" ")<<"更新价格"<<endl;
    cout<<"      "<<(nav==6?"*":" ")<<"导出信息"<<endl;
    cout<<"      "<<(nav==7?"*":" ")<<"退出"<<endl;
	cout<<"(w或s移动，空格进入模块)"<<endl;
    cout<<"========================"<<endl;
}

int main() 
{
    int choice;
    string name, category, label;
    int quantity;
    double price;
	importInventory("product.info");

    do{
/*	
 *	这边用宏判断是linux还是windows
 *	我这边用的是linux系统
*/
#ifdef _WIN32
		system("cls");
#elif __linux__
		system("clear");
#endif
        printMenu();
		displayInventory();
		char ch = getch();
		if(ch == 'w') nav = nav-1 == 0? 7:nav-1;
		else if(ch == 's') nav = nav+1 == 8? 1:nav+1;
		if(ch == ' ')
        switch(nav)
	   	{
            case 1:
                cout<<"输入产品名:";    cin>>name;
                cout<<"输入产品类别:";  cin>>category;
                cout<<"输入产品标签:";  cin>>label;
                cout<<"输入产品数量: "; cin>>quantity;
                cout<<"输入产品价格:";  cin>>price;
				addProduct(name, category, label, quantity, price);
                break;
            case 2:
                cout<<"输入删除的产品名:"; cin>>name;
				removeProduct(name);
                break;
            case 3:
                cout<<"输入要购买的产品:"; cin>>name;
                cout<<"输入购买数量: ";    cin>>quantity;
				purchaseProduct(name, quantity);
                break;
            case 4:
                cout<<"输入出售的产品:"; cin>>name;
                cout<<"输入出售数量:";   cin>>quantity;
				sellProduct(name, quantity);
                break;
            case 5:
                cout<<"输入要更新价格的产品名:"; cin>>name;
                cout<<"输入新价格:";             cin>>price;
				updatePrice(name, price);
                break;
			case 6:
				exportInventory("product.info");
				break;
            case 7:
                cout<<"已退出程序..."<<endl;
				exit(0);
        }
    } while(choice != 7);

    return 0;
}
#ifdef __linux__
int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
	//保存现在的终端设置
     if (tcgetattr(fd, &tm) < 0) return -1;

     tm_old = tm;

	//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     cfmakeraw(&tm);
	//设置上更改之后的设置
     if (tcsetattr(fd, TCSANOW, &tm) < 0) return -1;

     ch = getchar();

	//更改设置为最初的样子
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) return -1;
     return ch;
}
#endif
