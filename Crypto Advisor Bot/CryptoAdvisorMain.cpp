#include "CryptoAdvisorMain.h"

CryptoAdvisorMain::CryptoAdvisorMain() {
    //Loading Message to user
    std::cout << "\nCrypto Advisor Bot Loading! Please Wait .....\n\n" << std::flush;
    //Loading the CSV file
    orderBook.load("20200601.csv");
    //Variable to store current timestamp position
    timeStampPos = 0;
    timeStamp = orderBook.retTimestamps()[timeStampPos];
    helpCmdMsgs();
    registerCmd();
}

//Registering the commands inserted by the user
void CryptoAdvisorMain::registerCmd() {
    mainMenu.insert({"help", std::mem_fn(&CryptoAdvisorMain::helpCmd)});
    mainMenu.insert({"prod", std::mem_fn(&CryptoAdvisorMain::prodCmd)});
    mainMenu.insert({"min", std::mem_fn(&CryptoAdvisorMain::minCmd)});
    mainMenu.insert({"max", std::mem_fn(&CryptoAdvisorMain::maxCmd)});
    mainMenu.insert({"avg", std::mem_fn(&CryptoAdvisorMain::avgCmd)});
    mainMenu.insert({"predict", std::mem_fn(&CryptoAdvisorMain::predictCmd)});
    mainMenu.insert({"time", std::mem_fn(&CryptoAdvisorMain::timeCmd)});
    mainMenu.insert({"step", std::mem_fn(&CryptoAdvisorMain::stepCmd)});
    mainMenu.insert({"spread", std::mem_fn(&CryptoAdvisorMain::spreadCmd)});
    mainMenu.insert({"clear", std::mem_fn(&CryptoAdvisorMain::clearCmd)});
    mainMenu.insert({"exit", std::mem_fn(&CryptoAdvisorMain::exitCmd)});
}

//Inserting the description and how to use the commands for the help cmd menu 
void CryptoAdvisorMain::helpCmdMsgs() {
    helpCmd_menu.insert({"help", "Description:\nLists all available commands or output help for a specified command\n\nHow to use:\nhelp\n\thelp [command]"});
    helpCmd_menu.insert({"prod", "Description:\nLists all available products\n\nHow to use:\nprod"});
    helpCmd_menu.insert({"min", "Description:\nFind the minimum bid or ask for a product in the current timestamp\n\nHow to use:\nmin [product ex: ETH/BTC] [bid/ask]"});
    helpCmd_menu.insert({"max", "Description:\nFind the maximum bid or ask for a product in the current timestamp\n\nHow to use:\nmax [product ex: ETH/BTC] [bid/ask]"});
    helpCmd_menu.insert({"avg", "Description:\nFind the average ask or bid for the selected product over the sent number of timestamps\n\nHow to use:\navg [product ex: ETH/BTC] [bid/ask] [steps]"});
    helpCmd_menu.insert({"predict", "Description:\nPredict the max or min of an ask or a bid for the sent product for the next timestamp\n\nHow to use:\npredict [min/max] [product ex: ETH/BTC] [bid/ask]"});
    helpCmd_menu.insert({"time", "Description:\nDisplay the current time in the dataset, i.e. which timeframe are we looking at\n\nHow to use:\ntime"});
    helpCmd_menu.insert({"step", "Description:\nMove to the next time stamp\n\nHow to use:\nstep"});
    helpCmd_menu.insert({"spread", "Description:\nFind the spread of a product in the current timestamp\n\nHow to use:\nspread [product ex: ETH/BTC]"});
    helpCmd_menu.insert({"clear", "Description:\nClear the screen\n\nHow to use:\nclear"});
    helpCmd_menu.insert({"exit", "Description:\nExit the crypto advisor bot\n\nHow to use:\nexit"});
}
void CryptoAdvisorMain::start() {
    std::cout.precision(5);
    std::cout << std::fixed;

    //Message to user
    std::cout << "CryptoAdvisorBot> Please enter a command, or write \"help\" to show the list of all the available commands\nuser> ";
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> tokens = Tokeniser::tokenise(line, " ");
        runCmd(tokens);
        std::cout << "user> ";
    }
}
//If an invalid command is inserted a message is displayed to the user
void CryptoAdvisorMain::findCmd(const std::string &cmd) {
    if (mainMenu.find(cmd) == mainMenu.end()) {
        throw std::runtime_error("Error: The entered command \"" + cmd + "\" does not exist! Please enter a valid command.");
    }
}

//Validating inserted command and if no command is inserted, program will keep waiting for a command to process
void CryptoAdvisorMain::runCmd(std::vector<std::string> &tokens) {
    if (tokens.empty()) {
        return;
    }

    try {
        const auto &cmd = tokens[0];
        std::vector<std::string> arguments = {tokens.begin() + 1, tokens.end()};

        findCmd(cmd);
        mainMenu[cmd](*this, arguments);

    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
}

//Checking that the correct number of arguments are used when using the help command
void CryptoAdvisorMain::helpCmd(std::vector<std::string> &input) {
    if (input.size() > 1) {
        throw std::invalid_argument("Error: Number of arguments used does not match.");
    }

    if (input.size() == 1) {
        const auto &cmd = input[0];
        findCmd(cmd);

        std::cout << helpCmd_menu[cmd] << '\n';
        return;
    }

//List of all the available commands
    std::cout << "CryptoAdvisor> " << R"(Available commands:
    help                List all the available commands
    help [command]      Output help for a specified command
    prod                List all the available products
    min                 Find the minimum bid or ask of a product in the current timestamp
    max                 Find the maximum bid or ask of a product in the current timestamp
    avg                 Find the average ask or bid for the selected product over the sent number of timestamps
    spread              Find the market spread of a product in the current timestamp
    predict             Predict the max or min of an ask or a bid for the sent product for the next timestamp
    time                Display the current time in the dataset, i.e. Which timeframe are we looking at
    step                Move to the next timestamp
    clear               Clear the screen
    exit                Exit the crypto advisor bot
)";
}

//Displaying the product list when prod command is used
void CryptoAdvisorMain::prodCmd(std::vector<std::string> &input) {
    checkArgs(input, 0);

    std::cout << "CryptoAdvisor> " << "All the available products are:\n";
    for (const auto &product: orderBook.retProds()) {
        std::cout << "- " << product << '\n';
    }
}

//Displaying the minimum price when the min command is used
void CryptoAdvisorMain::minCmd(std::vector<std::string> &input) {
    checkArgs(input, 2);

    const auto product = orderBook.checkProductValid(input[0]);
    const auto orderType = Order::strToOrderType(input[1]);

    std::cout << "CryptoAdvisor> " << "The minimum " << input[1] << " price for " << product << " is: "
              << Arithmetic::min(orderBook.retPriFromOrd(timeStamp, product, orderType))
              << '\n';
}

//Displaying the maximum price when the max command is used
void CryptoAdvisorMain::maxCmd(std::vector<std::string> &input) {
    checkArgs(input, 2);

    const auto product = orderBook.checkProductValid(input[0]);
    const auto orderType = Order::strToOrderType(input[1]);

    std::cout << "CryptoAdvisor> " << "The maximum " << input[1] << " price for " << product << " is: "
              << Arithmetic::max(orderBook.retPriFromOrd(timeStamp, product, orderType))
              << '\n';
}


//Displaying the average price when the avg command is used
void CryptoAdvisorMain::avgCmd(std::vector<std::string> &input) {
    checkArgs(input, 3);

    const auto product = orderBook.checkProductValid(input[0]);
    const auto orderType = Order::strToOrderType(input[1]);
    const auto steps = std::stoi(input[2]);

    std::cout << "CryptoAdvisor> "
              << "The average " << product << ' ' << input[1] << " price over the last " << steps << " steps is: "
              << orderBook.avgTimeSteps(timeStampPos, product, orderType, steps)
              << '\n';
}

//Displaying the prediction price when the predict command is used
//Eror handling used to display message to the user if incorrect arguments are used
void CryptoAdvisorMain::predictCmd(std::vector<std::string> &input) {
    checkArgs(input, 3);

    if (timeStampPos == 0) {
        throw std::runtime_error("Error: Not enough info. Try again another time.");
    }

    const auto minmax = input[0];
    if (minmax != "max" && minmax != "min")
        throw std::invalid_argument("Error: The first parameter must be max or min.");
    const auto product = orderBook.checkProductValid(input[1]);
    const auto orderType = Order::strToOrderType(input[2]);

    std::cout << "CryptoAdvisor> "
              << "I predict that the " << minmax << ' ' << input[2] << " price for " << product << " will be "
              << orderBook.pricePred(minmax, product, orderType)
              << '\n';
}

//Displaying the current timestamp when the time command is used
void CryptoAdvisorMain::timeCmd(std::vector<std::string> &input) {
    checkArgs(input, 0);

    std::cout << "CryptoAdvisor> " << "The current time is: " << timeStamp << '\n';
}

//Moving to the next timestamp when the step command is used
void CryptoAdvisorMain::stepCmd(std::vector<std::string> &input) {
    checkArgs(input, 0);

    orderBook.updSts(timeStampPos);
    timeStampPos++;
    if (timeStampPos > orderBook.retTimestamps().size()) {
        timeStampPos--;
        throw std::out_of_range("Attention: End of timeline reached.");
    }
    timeStamp = orderBook.retTimestamps()[timeStampPos];

    std::cout << "CryptoAdvisor> " << "Moved to the next timestamp. The time is now : " << timeStamp << '\n';
}

//Clearing the screen when the clear command is used
void CryptoAdvisorMain::clearCmd(std::vector<std::string> &input) {
    checkArgs(input, 0);
    system("clear||cls");
}

//Displaying the spread value when the spread command is used
void CryptoAdvisorMain::spreadCmd(std::vector<std::string> &input) {
    checkArgs(input, 1);

    const auto product = orderBook.checkProductValid(input[0]);

    std::cout << "CryptoAdvisor> " << "The spread for " << product << " is: "
              << Arithmetic::spread(
                      orderBook.retPriFromOrd(timeStamp, product, OrderType::ask),
                      orderBook.retPriFromOrd(timeStamp, product, OrderType::bid))
              << '\n';
}

//Exit the Crypto Advisor Bot
void CryptoAdvisorMain::exitCmd(std::vector<std::string> &input) {
    checkArgs(input, 0);
    exit(0);
}

//Checking the number of arguments used. If invalid a message is shown to the user
void CryptoAdvisorMain::checkArgs(const std::vector<std::string> &input, int size) {
    if (input.size() != size) {
        std::string e = (input.size() > size ? "more" : "less");
        throw std::invalid_argument("Error: The number of arguments used does not match. You used " + e + " arguments than required!");
    }
}
