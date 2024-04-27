/*
 * 此项目已在Github开源
 * 项目地址:https://github.com/OxiaozhaiO/IMS
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>

/*
 * 我需要getch函数，但linux没有，所以需要自己实现
 * 这边判断是windows还是linux
 * 如果是linux就用自己实现的getch
 * 如果是windows就用conio里面的getch
 */
#ifdef __linux__
#include <unistd.h>
#include <termio.h>
#include <fcntl.h>
int getch();

#elif _WIN32
#include <conio.h>

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

    Product(string& n, string& c, string& l, int q, double p)
        : name(n), category(c), label(l), quantity(q), price(p) {}
};

class IMS
{
private:
	//用栈将库存保存起来（非常的形象生动）
    stack<Product> inventory;
public:
	//添加产品函数
    void addProduct(string& name, string& category, string& label, int quantity, double price) 
	{
        inventory.push(Product(name, category, label, quantity, price));
        cout << "添加了: " << name<< endl;
    }
	//删除产品函数
    void removeProduct(string& name) 
	{
        stack<Product> temp;//遍历栈需要pop, 所以防止数据丢失建立temp栈保存
        while (!inventory.empty()) 
		{
            Product product = inventory.top();
            inventory.pop();
            if (product.name != name) temp.push(product);
			else cout << "已删除: " << name << endl;
        }
        while (!temp.empty()) //将数据放回原栈
		{
            inventory.push(temp.top());
            temp.pop();
        }
    }
	//显示库存函数
    void displayInventory() 
	{
        cout << "当前库存:" << endl;
		if(inventory.empty())cout<<"-----------\n";
		else cout<<"==\n";

        stack<Product> temp;//建立temp栈保存数据
        while (!inventory.empty()) 
		{
            Product product = inventory.top();
            inventory.pop();
            cout << "名字: " << product.name << ", 类别: " << product.category
                 << ", 标签: " << product.label << ", 数量: " << product.quantity
                 << ", 价格: " << product.price << endl;
            temp.push(product);

        }
        while (!temp.empty()) //放回原栈中
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
        while (!inventory.empty()) 
		{
            Product product = inventory.top();
            inventory.pop();
            if (product.name == name) 
			{
                product.quantity += quantity;
                temp.push(product);
                cout << "购买了" << quantity << "个" << name << endl;
            } else temp.push(product); 
        }

        while (!temp.empty()) 
		{
            inventory.push(temp.top());
            temp.pop();
        }
    }
	//产品售出函数
    void sellProduct(string& name, int quantity) 
	{
        stack<Product> temp;
        while (!inventory.empty()) 
		{
            Product product = inventory.top();
            inventory.pop();
            if (product.name == name) 
			{
                if (product.quantity < quantity) 
				{
                    cout << name << " 数量不足!" << endl;
                    temp.push(product);
                    break;
                }
                product.quantity -= quantity;
                temp.push(product);
                cout << "已出售" << quantity << "个" << name << endl;
            } else temp.push(product);
        }

        while (!temp.empty()) 
		{
            inventory.push(temp.top());
            temp.pop();
        }
    }
	//更新价格函数
    void updatePrice(string& name, double price) 
	{
        stack<Product> temp;
        while (!inventory.empty()) 
		{
            Product product = inventory.top();
            inventory.pop();
            if (product.name == name) 
			{
                product.price = price;
                temp.push(product);
                cout << name << " 的价格已改为" << price << endl;
            } else temp.push(product);
        }

        while (!temp.empty()) 
		{
            inventory.push(temp.top());
            temp.pop();
        }
    }
};
//打印主菜单
void printMenu() 
{
    cout << "====超市进销管理系统====" << endl;
	cout << "      "<<(nav==1?"*":" ")<<"添加产品" << endl;
    cout << "      "<<(nav==2?"*":" ")<<"删除产品" << endl;
    cout << "      "<<(nav==3?"*":" ")<<"购买产品" << endl;
    cout << "      "<<(nav==4?"*":" ")<<"售出产品" << endl;
    cout << "      "<<(nav==5?"*":" ")<<"更新价格" << endl;
    cout << "      "<<(nav==6?"*":" ")<<"退出" << endl;
	cout << "(w或s移动，空格进入模块)"<<endl;
    cout << "========================" << endl;
}

int main() 
{
    IMS ims;
    int choice;
    string name, category, label;
    int quantity;
    double price;
    do {
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
		ims.displayInventory();
		char ch = getch();
		if(ch == 'w') nav = nav-1==0?6:nav-1;
		else if(ch == 's') nav = nav+1==7?1:nav+1;
		if(ch == ' ')
        switch (nav)
	   	{
            case 1:
                cout << "输入产品名:";
                cin >> name;
                cout << "输入产品类别:";
                cin >> category;
                cout << "输入产品标签:";
                cin >> label;
                cout << "输入产品数量: ";
                cin >> quantity;
                cout << "输入产品价格:";
                cin >> price;
                ims.addProduct(name, category, label, quantity, price);
                break;
            case 2:
                cout << "输入删除的产品名:";
                cin >> name;
                ims.removeProduct(name);
                break;
            case 3:
                cout << "输入要购买的产品:";
                cin >> name;
                cout << "输入购买数量: ";
                cin >> quantity;
                ims.purchaseProduct(name, quantity);
                break;
            case 4:
                cout << "输入出售的产品:";
                cin >> name;
                cout << "输入出售数量:";
                cin >> quantity;
                ims.sellProduct(name, quantity);
                break;
            case 5:
                cout << "输入要更新价格的产品名:";
                cin >> name;
                cout << "输入新价格:";
                cin >> price;
                ims.updatePrice(name, price);
                break;
            case 6:
                cout << "已退出程序...\n"<< endl;
				exit(0);
        }
    } while (choice != 7);

    return 0;
}
#ifdef __linux__
int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }

     return ch;
}
#endif
