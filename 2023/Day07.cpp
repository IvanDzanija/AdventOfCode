//
//  Day07.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

int handType(std::string currentHand){
	std::map<char, int> type;
	int maxi = 0;
	char maxCard = ' ';
	int prevMaxi = 0;
	for (int i = 0; i < 5; ++i){
		char currentCard = currentHand[i];
		type[currentCard] += 1;
		if (type[currentCard] > maxi){
			prevMaxi = maxi;
			maxi = type[currentCard];
			maxCard = currentCard;
		}
	}
	if (type.find('1') != type.end() && maxCard != '1'){
		maxi += type.at('1');
		type.erase(type.find('1'));
	}
	else if (type.find('1') != type.end() && maxCard == '1'){
		type.erase(type.find('1'));
		int nextMax = 0;
		for (auto& x: type) {
			if (x.second > nextMax) nextMax = x.second;
		}
		maxi += nextMax;
	}
	
	
	if (maxi == 5) return 6;
	else if (maxi == 4) return 5;
	else if (maxi == 3){
		if (type.size() == 2) return 4;
		else return 3;
	}
	else if (maxi == 2){
		if(type.size() == 3) return 2;
		else return 1;
	}
	else return 0;
}

void day7_1(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;

	std::map <std::string, int> handBets;
	std::vector<std::string> fiveOfKind;
	std::vector<std::string> fourOfKind;
	std::vector<std::string> fullHouse;
	std::vector<std::string> threeOfKind;
	std::vector<std::string> twoPair;
	std::vector<std::string> onePair;
	std::vector<std::string> highCard;
	int numOfPlayers = 0;
	while (getline(inputFile, currentLine)){
		std::string currentHand;
		++numOfPlayers;
		int currentBet = 0;
		for (int i = 0; i < 5; ++i){
			if (currentLine[i] == 'T') currentLine[i] = '9' + 1;
			else if (currentLine[i] == 'J') currentLine[i] = '9' + 2;
			else if (currentLine[i] == 'Q') currentLine[i] = '9' + 3;
			else if (currentLine[i] == 'K') currentLine[i] = '9' + 4;
			else if (currentLine[i] == 'A') currentLine[i] = '9' + 5;

			currentHand += currentLine[i];
		}
		for (int i = 6; i < currentLine.size(); ++i){
			currentBet = currentBet * 10 + currentLine[i] - '0';
		}
		handBets[currentHand] = currentBet;
		int handTypeC = handType(currentHand);
		if (handTypeC == 6) fiveOfKind.push_back(currentHand);
		else if (handTypeC == 5) fourOfKind.push_back(currentHand);
		else if (handTypeC == 4) fullHouse.push_back(currentHand);
		else if (handTypeC == 3) threeOfKind.push_back(currentHand);
		else if (handTypeC == 2) twoPair.push_back(currentHand);
		else if (handTypeC == 1) onePair.push_back(currentHand);
		else if (handTypeC == 0) highCard.push_back(currentHand);
	}
	sort(fiveOfKind.begin(), fiveOfKind.end());
	sort(fourOfKind.begin(), fourOfKind.end());
	sort(fullHouse.begin(), fullHouse.end());
	sort(threeOfKind.begin(), threeOfKind.end());
	sort(twoPair.begin(), twoPair.end());
	sort(onePair.begin(), onePair.end());
	sort(highCard.begin(), highCard.end());

	int result;
	for (int i = fiveOfKind.size() - 1; i >= 0; --i)
	{
		result += (handBets[fiveOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = fourOfKind.size() - 1; i >= 0; --i)
	{
		result += (handBets[fourOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = fullHouse.size() - 1; i >= 0; --i)
	{
		result += (handBets[fullHouse.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = threeOfKind.size() - 1; i >= 0; --i)
	{
		result += (handBets[threeOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = twoPair.size() - 1; i >= 0; --i)
	{
		result += (handBets[twoPair.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	 for (int i = onePair.size() - 1; i >= 0; --i)
	{
		result += (handBets[onePair.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	 for (int i = highCard.size() - 1; i >= 0; --i)
	{
		result += (handBets[highCard.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	std::cout<<"Part 1: " << result << std::endl;


}


void day7_2(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;

	std::map <std::string, int> handBets;
	std::vector<std::string> fiveOfKind;
	std::vector<std::string> fourOfKind;
	std::vector<std::string> fullHouse;
	std::vector<std::string> threeOfKind;
	std::vector<std::string> twoPair;
	std::vector<std::string> onePair;
	std::vector<std::string> highCard;
	int numOfPlayers = 0;
	while (getline(inputFile, currentLine)){
		std::string currentHand;
		++numOfPlayers;
		int currentBet = 0;
		for (int i = 0; i < 5; ++i){
			if (currentLine[i] == 'T') currentLine[i] = '9' + 1;
			else if (currentLine[i] == 'J') currentLine[i] = '1';
			else if (currentLine[i] == 'Q') currentLine[i] = '9' + 3;
			else if (currentLine[i] == 'K') currentLine[i] = '9' + 4;
			else if (currentLine[i] == 'A') currentLine[i] = '9' + 5;

			currentHand += currentLine[i];
		}
		for (int i = 6; i < currentLine.size(); ++i){
			currentBet = currentBet * 10 + currentLine[i] - '0';
		}
		handBets[currentHand] = currentBet;
		int handTypeC = handType(currentHand);
		if (handTypeC == 6) fiveOfKind.push_back(currentHand);
		else if (handTypeC == 5) fourOfKind.push_back(currentHand);
		else if (handTypeC == 4) fullHouse.push_back(currentHand);
		else if (handTypeC == 3) threeOfKind.push_back(currentHand);
		else if (handTypeC == 2) twoPair.push_back(currentHand);
		else if (handTypeC == 1) onePair.push_back(currentHand);
		else if (handTypeC == 0) highCard.push_back(currentHand);
	}
	sort(fiveOfKind.begin(), fiveOfKind.end());
	sort(fourOfKind.begin(), fourOfKind.end());
	sort(fullHouse.begin(), fullHouse.end());
	sort(threeOfKind.begin(), threeOfKind.end());
	sort(twoPair.begin(), twoPair.end());
	sort(onePair.begin(), onePair.end());
	sort(highCard.begin(), highCard.end());

	int ans = 0;
	for (int i = fiveOfKind.size() - 1; i >= 0; --i)
	{
		ans += (handBets[fiveOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = fourOfKind.size() - 1; i >= 0; --i)
	{

		ans += (handBets[fourOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = fullHouse.size() - 1; i >= 0; --i)
	{

		ans += (handBets[fullHouse.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = threeOfKind.size() - 1; i >= 0; --i)
	{

		ans += (handBets[threeOfKind.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	for (int i = twoPair.size() - 1; i >= 0; --i)
	{
		
		ans += (handBets[twoPair.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	 for (int i = onePair.size() - 1; i >= 0; --i)
	{
		
		ans += (handBets[onePair.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	 for (int i = highCard.size() - 1; i >= 0; --i)
	{
		
		ans += (handBets[highCard.at(i)] * numOfPlayers);
		--numOfPlayers;
	}
	std::cout << "Part 2: " << ans << std::endl;
}

void day7(void){
	day7_1();
	day7_2();
}
