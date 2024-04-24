/*
 * 此项目已在Github开源
 * 项目地址:https://github.com/OxiaozhaiO/IMS
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

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
    cout << "      1.添加产品" << endl;
    cout << "      2.删除产品" << endl;
    cout << "      3.显示产品" << endl;
    cout << "      4.购买产品" << endl;
    cout << "      5.售出产品" << endl;
    cout << "      6.更新价格" << endl;
    cout << "      7.退出" << endl;
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
 *	我这边用的是linux
*/
#ifdef _WIN32
		system("cls");
#elif __linux__
		system("clear");
#endif
        printMenu();
		ims.displayInventory();
    	cout << "输入序号:";
        cin >> choice;
        switch (choice)
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
                ims.displayInventory();
                break;
            case 4:
                cout << "输入要购买的产品:";
                cin >> name;
                cout << "输入购买数量: ";
                cin >> quantity;
                ims.purchaseProduct(name, quantity);
                break;
            case 5:
                cout << "输入出售的产品:";
                cin >> name;
                cout << "输入出售数量:";
                cin >> quantity;
                ims.sellProduct(name, quantity);
                break;
            case 6:
                cout << "输入要更新价格的产品名:";
                cin >> name;
                cout << "输入新价格:";
                cin >> price;
                ims.updatePrice(name, price);
                break;
            case 7:
                cout << "已退出程序...\n"<< endl;
				exit(0);
            default:
                cout << "没有这个选项" << endl;
                break;
        }
		getchar();
		getchar();
    } while (choice != 7);

    return 0;
}
