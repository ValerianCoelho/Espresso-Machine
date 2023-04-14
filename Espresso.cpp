#include <iostream>
#include <cstdlib>
#include <string>
#include <ios>
#include <stdio.h>
#include <conio.h>
#include <fstream>

using namespace std;

#define HighlightLen 30

int NewChoice, OldChoice;

int hello;

// TUI Library -------------------------------------------------------------------------------------------------------------

void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

void space(int n)
{
    for(int i=0; i<n ;i++)
        cout << " ";
}

void display(string header, string options[], int n, int initialOptionHighlight)
{
    system("cls");
    cout << header << endl;
    for(int i=0; i<n; i++)
    {
        if(i+1 == initialOptionHighlight)
        {
            cout << i+1 << ") \033[30;107m" << options[i];
            space(HighlightLen-options[i].length());
            cout << "\n\033[0m";
            continue;
        }
        cout << i+1 << ") " << options[i] << endl;
    }
    cout << "Enter : ";
}

void UpdateDisplay(string options[], int n)
{
    if(NewChoice == OldChoice)
        return;

    //Removing Highlight From Previous Choice
    gotoxy(4, OldChoice+2);
    cout << options[OldChoice];
    space(HighlightLen-options[OldChoice].length());

    //Printing Highlight to new Choice
    gotoxy(4, NewChoice+2);
    cout << "\033[30;107m" << options[NewChoice];
    space(HighlightLen-options[NewChoice].length());
    cout << "\033[0m";

    OldChoice = NewChoice;

}

int WhiteHighlight(string header, string options[], int NumberOfOptions, int initialOptionHighlight)
{
    char ch;
    cout << header;
    NewChoice = OldChoice = initialOptionHighlight-1;
    display(header, options, NumberOfOptions, initialOptionHighlight);
    do
    {
        ch = getch();

        //Takes Input From the Keyboard
        if(ch==75 || ch==72)
        {
            if(NewChoice==0)
                continue;
            NewChoice--;
        }
        else if(ch==77 || ch==80)
        {
            if(NewChoice==NumberOfOptions-1)
                continue;
            NewChoice++;
        }
        UpdateDisplay(options, NumberOfOptions);
    }while(ch!=13);
    system("cls");
    return NewChoice+1;
}

// Format Library ----------------------------------------------------------------------------------------------------------

string multiplyInput(string text = "", int width = 0){
    string newText = "";
    for(int i=0; i<width; i++){
        newText += text;
    }
    return newText;
}

void alignCenter(string text = "", int width = 0, string leftText = "", string rightText = ""){
    int left = (width - text.length())/2;
    int right = width - (left + text.length());
    cout << leftText;
    cout.width(left + text.length());
    cout.fill(' ');
    cout << text;
    cout.width(right);
    cout << "";
    cout << rightText;
}

string returnCenterAligned(string text = "", int width = 0, string leftText = "", string rightText = ""){
    int left = (width - text.length())/2;
    int right = width - (left + text.length());
    return leftText + multiplyInput(" ", left) + text + multiplyInput(" ", right) + rightText;
}

void alignLeft(string text = "", int width = 0, string leftText = "", string rightText = ""){
    cout << leftText;
    cout.width(width);
    cout << left;
    cout << text;
    cout << rightText;
}

string returnLeftAligned(string text = "", int width = 0, string leftText = "", string rightText = ""){
    return leftText + text + multiplyInput(" ", width - text.length()) + rightText;
}

string formatFloat(float num){
    string formatedNumber = "";
    string newNum = to_string(int(num * 100));
    if(num == 0)
        formatedNumber = formatedNumber + to_string(int(num)) + "." + "00";
    else
        formatedNumber = formatedNumber + to_string(int(num)) + "." + newNum[newNum.length()-2] + newNum[newNum.length()-1];
    return formatedNumber;
}

// Class Declarations ------------------------------------------------------------------------------------------------------

class Coffee{
    private:
        int coffeeChoice;
        int cupSizeChoice;

        float coffeePrices[5];
        float sizeMultipliers[3];

        string coffeeFlavours[5];
        string cupSizes[3];
    public:
        Coffee(); // This Constructor sets the coffee Flavours and coffee cup sizes

        void displayMenu(int index); // This function displays the Items in the menu
        void displaySize(); // This function displays the coffee cup sizes

        float getPrice(); // This function returns the price of the coffee ordered
        string getCoffeeFlavour() { // This function returns the names of the coffee flavours
            string coffeeFlavoursWithoutSpacing[5] = {"Café Crème", "Caffè latte", "Caffè macchiato", "Cappuccino", "Latte Macchiato"};
            return coffeeFlavoursWithoutSpacing[coffeeChoice-1];
            };
};

class User{
    private:
        string name;
        long long phoneno;
    public:
        User(); // This constructor accepts the details of the customer
        string getName() {return name;}
        long long getPhoneno() {return phoneno;}
};

class Reciept: public Coffee, public User{
    private:
        float subTotal;
        float discount;
        float tax;
        float total;
    public:
        void calculateTotalBill(Coffee c[], int n); // Sets the values of subTotal, discount, tax and total
        void displayReciept(Coffee c[], int n); // Displays the Reciept of the customer
        void printReciept(Coffee c[], int n); // Prints the Reciept in a txt file
};

// Class Constructors definitions ------------------------------------------------------------------------------------------

Coffee :: Coffee()
{
    float coffeePricesone[5] = {75, 80, 75, 70, 80};
    float sizeMultipliersone[3] = {1, 1.5 , 2};
    string cupSizesone[3] = {"Small", "Medium", "Large"};
    string coffeeFlavoursone[5] = {"Café Crème               Rs. 75", "Caffè latte              Rs. 80", "Caffè macchiato          Rs. 75", "Cappuccino               Rs. 70", "Latte Macchiato          Rs. 80"};

    for(int i=0; i<3; i++){
        cupSizes[i] = cupSizesone[i];
        sizeMultipliers[i] = sizeMultipliersone[i];
    }
    for(int i=0; i<5; i++){
        coffeeFlavours[i] = coffeeFlavoursone[i];
        coffeePrices[i] = coffeePricesone[i];
    }
}

User :: User(){
    cout << "Enter your name : ";
    getline(cin, name);

    cout << "Enter your phone no : ";
    cin >> phoneno;
}

// Class member function definitions ---------------------------------------------------------------------------------------

void Coffee :: displayMenu(int index){
    coffeeChoice = WhiteHighlight("Place Your Order no : " + to_string(index+1), coffeeFlavours, 5, 1);
}

void Coffee :: displaySize(){
    cupSizeChoice = WhiteHighlight("Choose Your Coffee Cup Size", cupSizes, 3, 1);
}

float Coffee :: getPrice(){
    return coffeePrices[coffeeChoice-1]*sizeMultipliers[cupSizeChoice-1];
}

void Reciept :: displayReciept(Coffee c[], int n){
    int totalRecieptWidth = 28 + formatFloat(total).length();

    cout << "┌" << multiplyInput("─", totalRecieptWidth + 2) << "┐" << endl;
    alignCenter("Espresso Machine", totalRecieptWidth, "│ ", " │"); cout << endl;
    cout << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    alignLeft("Name : " + getName(), totalRecieptWidth, "│ ", " │"); cout << endl;
    alignLeft("Phone no : " + to_string(getPhoneno()), totalRecieptWidth, "│ ", " │"); cout << endl;
    cout << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    alignLeft("ITEMS" + multiplyInput(" ", 19) + "PRICE", totalRecieptWidth, "│ ", " │"); cout << endl;
    for(int i=0; i<n; i++){
        alignLeft(c[i].getCoffeeFlavour() + multiplyInput(" ", (24-c[i].getCoffeeFlavour().length())) + "Rs. " + formatFloat(c[i].getPrice()), totalRecieptWidth, "│ ", " │"); cout << endl;
    }
    cout << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    alignLeft("SUB TOTAL" + multiplyInput(" ", 15) + "Rs. " + formatFloat(subTotal), totalRecieptWidth, "│ ", " │"); cout << endl;
    alignLeft("DISCOUNT" + multiplyInput(" ", 16) + "Rs. " + formatFloat(discount), totalRecieptWidth, "│ ", " │"); cout << endl;
    alignLeft("TAX" + multiplyInput(" ", 21) + "Rs. " + formatFloat(tax), totalRecieptWidth, "│ ", " │"); cout << endl;
    cout << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    alignLeft("TOTAL" + multiplyInput(" ", 19) + "Rs. " + formatFloat(total), totalRecieptWidth, "│ ", " │"); cout << endl;
    cout << "└" << multiplyInput("─", totalRecieptWidth + 2) << "┘" << endl;
}

void Reciept :: calculateTotalBill(Coffee c[], int n){
    // For orders more than 150 Rs you get discount of 5%
    // For orders more than 250 Rs you get discount of 10%
    // For orders more than 500 Rs you get discount of 20%

    subTotal = 0;
    // Calculates sub Total
    for(int i=0; i<n; i++)
        subTotal += c[i].getPrice();

    // Calulates discount
    if(subTotal > 500)    discount = subTotal*0.2;   
    else if(subTotal > 250)    discount = subTotal*0.1;
    else if(subTotal > 150)    discount = subTotal*0.05;
    else discount = 0.0;

    // Calculates the total before tax
    total = subTotal - discount;

    // Calculates Tax
    tax = total * 0.18;

    // Calculates the Total after tax
    total = total + tax;
}

void Reciept :: printReciept(Coffee c[], int n){
    ofstream recieptPtr;
    recieptPtr.open("Reciept.txt");
    int totalRecieptWidth = 28 + formatFloat(total).length();

    recieptPtr << "┌" << multiplyInput("─", totalRecieptWidth + 2) << "┐" << endl;
    recieptPtr << returnCenterAligned("Espresso Machine", totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    recieptPtr << returnLeftAligned("Name : " + getName(), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << returnLeftAligned("Phone no : " + to_string(getPhoneno()), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    recieptPtr << returnLeftAligned("ITEMS" + multiplyInput(" ", 19) + "PRICE", totalRecieptWidth, "│ ", " │") << endl;
    for(int i=0; i<n; i++){
        recieptPtr << returnLeftAligned(c[i].getCoffeeFlavour() + multiplyInput(" ", (24-c[i].getCoffeeFlavour().length())) + "Rs. " + formatFloat(c[i].getPrice()), totalRecieptWidth, "│ ", " │") << endl;
    }
    recieptPtr << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    recieptPtr << returnLeftAligned("SUB TOTAL" + multiplyInput(" ", 15) + "Rs. " + formatFloat(subTotal), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << returnLeftAligned("DISCOUNT" + multiplyInput(" ", 16) + "Rs. " + formatFloat(discount), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << returnLeftAligned("TAX" + multiplyInput(" ", 21) + "Rs. " + formatFloat(tax), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << "├" << multiplyInput("─", totalRecieptWidth + 2) << "┤" << endl;
    recieptPtr << returnLeftAligned("TOTAL" + multiplyInput(" ", 19) + "Rs. " + formatFloat(total), totalRecieptWidth, "│ ", " │") << endl;
    recieptPtr << "└" << multiplyInput("─", totalRecieptWidth + 2) << "┘" << endl;
    recieptPtr.close();
}

// Main Function --------------------------------------------------------------------------------------------------------

int main(){
    int no_of_orders;
    cout << "Enter the number of orders you want to make : ";
    cin >> no_of_orders;
    cin.ignore();

    Coffee c[no_of_orders];
    Reciept r;

    for(int i=0; i<no_of_orders; i++){
        c[i].displayMenu(i);
        c[i].displaySize();
    }

    r.calculateTotalBill(c, no_of_orders);
    r.displayReciept(c, no_of_orders);
    getch();
    
    string booleanChoice[2] = {"Yes", "No"};
    int choice = WhiteHighlight("Do you want to print the reciept", booleanChoice, 2, 1);

    if(choice == 1){
        r.printReciept(c, no_of_orders);
    }
    cout << "Thankyou for visiting us " << r.getName() << ", and have a great day ahead!!!" << endl;
    getch();
    system("pause");
    return 0;
}
