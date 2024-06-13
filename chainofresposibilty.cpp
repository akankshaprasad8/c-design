#include <iostream>
using namespace std;

class LogProcessor{
public:
    int INFO=1;
    int ERROR=2;
    int DEBUG=3;
    LogProcessor* next;
    virtual void log(int logLevel, string message) {
        if(next != NULL)
            next->log(logLevel, message);
    }
};

class InfoLogProcessor: public LogProcessor{
public:
    InfoLogProcessor(LogProcessor* next) {
        this->next = next;
    }
    void log(int logLevel, string message) override {
        if(INFO == logLevel) {
            cout << "In info: " << message << endl;
        } else {
            LogProcessor::log(logLevel, message);
        }
    }
};

class ERRORLogProcessor: public LogProcessor{
public:
    ERRORLogProcessor(LogProcessor* next) {
        this->next = next;
    }
    void log(int logLevel, string message) override {
        if(ERROR == logLevel) {
            cout << "In error: " << message << endl;
        } else {
            LogProcessor::log(logLevel, message);
        }
    }
};

class DebugLogProcessor: public LogProcessor{
public:
    DebugLogProcessor(LogProcessor* next) {
        this->next = next;
    }
    void log(int logLevel, string message) override {
        if(DEBUG == logLevel) {
            cout << "In debug: " << message << endl;
        } else {
            LogProcessor::log(logLevel, message);
        }
    }
};

int main() {
    LogProcessor* logger = new DebugLogProcessor(new ERRORLogProcessor(new InfoLogProcessor(NULL)));
    
    logger->log(1, "This is an info message.");
    logger->log(2, "This is an error message.");
    logger->log(3, "This is a debug message.");

    delete logger;
    
    return 0;
}
