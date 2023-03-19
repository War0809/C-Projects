#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstdlib>

#include "Tokeniser.h"
#include "OrderBook.h"

class CryptoAdvisorMain {
public:
    // Create and load the advisor
    CryptoAdvisorMain();

    // Starting the program
    void start();

private:

    //Function to register the help messages
    void helpCmdMsgs();

    //Function to register the user commands
    void registerCmd();

    /**
     * Function to call a command
     * @param tokens A vector of strings containing the commands and its respective arguments
     */
    void runCmd(std::vector<std::string> &tokens);

    /**
     * Function to check if the entered command exists or not
     * @param cmd
     */
    void findCmd(const std::string &cmd);

    /**
     * Function to check that the entered command has the right number of arguments
     * @param input A vector of arguments
     * @param size The correct number of arguments
     */
    static void checkArgs(const std::vector<std::string> &input, int size);

    /**
     * Display help messages to the user
     * @param input A vector of arguments
     */
    void helpCmd(std::vector<std::string> &input);

    /**
     * Display all the available products to the user
     * @param input A vector of arguments
     */
    void prodCmd(std::vector<std::string> &input);

    /**
     * Calculate the minimum price for the selected product
     * @param input A vector of arguments
     */
    void minCmd(std::vector<std::string> &input);

    /**
     * Calculate the maximum price for the selected product
     * @param input A vector of arguments
     */
    void maxCmd(std::vector<std::string> &input);

    /**
     * Calculate the average bid or ask for the selected product over a number of timesteps
     * @param input A vector of arguments
     */
    void avgCmd(std::vector<std::string> &input);

    /**
     * Predict the min or max for an ask or bid for the selected product
     * @param input A vector of arguments
     */
    void predictCmd(std::vector<std::string> &input);

    /**
     * Output the current time read from the CSV file
     * @param input A vector of arguments
     */
    void timeCmd(std::vector<std::string> &input);

    /**
     * Move to the next time step in the CSV file
     * @param input A vector of arguments
     */
    void stepCmd(std::vector<std::string> &input);

    /**
     * Clear the screen
     * @param input A vector of arguments
     */
    void clearCmd(std::vector<std::string> &input);

    /**
     * Exit the Crypro Advisor Bot
     * @param input A vector of arguments
     */
    void exitCmd(std::vector<std::string> &input);


    /**
     * Calculate the spread for a selected product
     * @param input A vector of arguments
     */
    void spreadCmd(std::vector<std::string> &input);
    

    // The Current timestamp being used from the CSV file
    int timeStampPos;
    std::string timeStamp;

    // The OrderBook used to store data from the provided CSV file
    OrderBook orderBook;

    // Map of commands mapped to their name
    std::map<std::string, std::function<void(CryptoAdvisorMain &, std::vector<std::string> &args)>> mainMenu;

    // Map of help commands mapped to their name
    std::map<std::string, std::string> helpCmd_menu;
};




