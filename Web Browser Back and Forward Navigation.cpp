#include<iostream>
#include<string>
#include<stack>
#include<fstream>
#include<vector>

using namespace std;
class Page {
public:
	string url;
	string title;
	string content;

	Page(string u = "", string t = "", string c = "")
		:url(u), title(t), content(c) {}

	void display()const {
		cout << "Title:" << title << endl;
		cout << "URL:" << url << endl;
		cout << "Content:" << content << endl;
	}
};

class Browser {
private:
	stack<Page> backStack;
	stack<Page> forwardStack;
	Page currentPage;

public:
	//Navigation functions
	void visitNewPage(const Page& newPage) {
		if (!(currentPage.url.empty() && 
			currentPage.title.empty() &&
			currentPage.content.empty())) {
			backStack.push(currentPage);
		}
		currentPage = newPage;
		while (!forwardStack.empty()) {
			forwardStack.pop();
		}

		cout << "Visited:" << currentPage.title << endl;

	}
	void goBack() {
		if (!backStack.empty()) {
			forwardStack.push(currentPage);
			currentPage = backStack.top();
			backStack.pop();

			cout << "Went back to:" << currentPage.title << endl;
		}
		else {
			cout << "Back Stack is empty" << endl;
		}
	}
	void goForward() {
		if (!forwardStack.empty()) {
			backStack.push(currentPage);
			currentPage = forwardStack.top();
			forwardStack.pop();

			cout << "Went forward to:" << currentPage.title << endl;
		}
		else {
			cout << "Forward stack is empty" << endl;
		}
	}
	// Session management
	void saveSession(const string& filename = "session.txt") {
		ofstream outFile(filename);
		if (outFile) {
			outFile << currentPage.url << endl;
			outFile << currentPage.title << endl;
			outFile << currentPage.content << endl;
			outFile.close();

			cout << "Session saved successfully:" << endl;
		}
		else {
			cout << "Error saving session." << endl;
		}
	}
	void loadSession(const string& filename = "session.txt") {
		ifstream inFile(filename);
		if (inFile) {
			string url, title, content;
			getline(inFile, url);
			getline(inFile, title);
			getline(inFile, content);
			inFile.close();

			currentPage = Page(url, title, content);
			cout << "Session loaded.Current page." << currentPage.title << endl;
		}
		else {
			cout << "No saved session found." << endl;
		}
	}

	void showCurrentPage() {
		if (!currentPage.url.empty()) {
			currentPage.display();
		}
		else {
			cout << "No page is currently loaded." << endl;
		}
	}
	void printStack(const stack<Page>& s) {

		stack<Page> temp = s;

		if (temp.empty()) {
			cout << "empty" << endl;
			return;
		}
		vector<Page> pages;
		while (!temp.empty()) {
			pages.push_back(temp.top());
			temp.pop();

		}
		reverse(pages.begin(), pages.end());
		for (size_t i = 0; i < pages.size(); i++) {
			cout << "\n" << i + 1 << "." << pages[i].title
				<< "(" << pages[i].url << ")";
		}
		cout << endl;
	}
	void showHistory() {
		cout << "BackStack:";
		printStack(backStack);
		cout << "ForwardStack:";
		printStack(forwardStack);
	}
	void resetHistory() {
		backStack = stack<Page>();
		forwardStack = stack <Page>();
		currentPage = Page();
		cout << " Navigation history reset" << endl;
	}
};


// User interaction via a menu
int main(){
	Browser browser;
	browser.loadSession();

	int choice;
	do{
		cout << "Browser Menu" << endl;
		cout << "1.Visit New Page" << endl;
		cout << "2.Go back" << endl;
		cout << "3.Go forward" << endl;
		cout << "4.Show Current Page" << endl;
		cout << "5.Exit" << endl;
		cout << "6.Show History" << endl;
		cout << "7.Reset History" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;
		cin.ignore();

		switch(choice) {
		case 1: {
			string url, title, content;
			cout << "Enter URL:";
			getline(cin, url);
			cout << "Enter title:";
			getline(cin, title);
			cout << "Enter content:";
			getline(cin, content);
			browser.visitNewPage(Page(url, title, content));
			break;
		}
			
		case 2:
			browser.goBack();
			break;
		case 3:
			browser.goForward();
			break;
		case 4: 
			browser.showCurrentPage();
			break;
		case 5: 
			browser.saveSession();
			cout << "Exiting browser" << endl;
			break;
		case 6:
			browser.showHistory();
			break;
		case 7:
			browser.resetHistory();
			break;
		default:
			cout << "Invalid choice" << endl;
		}
		} while (choice != 5);
			  
			  return 0;
		}


