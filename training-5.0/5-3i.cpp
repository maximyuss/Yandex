// https://contest.yandex.ru/contest/59541/problems/I/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>
#include <cctype>

using namespace std;

struct structTeam {
	size_t id;
	size_t games;
	size_t goals;
	size_t firstGoals;
};

struct structPlayer {
	size_t id;
	size_t idTeam;
	size_t goals;
	size_t firstGoals;
	size_t times[91];
};

const string startOfRequest[4]{ "Total", "Mean ", "Goals", "Score" };
const string typeOfRequest[7]{ "Total goals f", "Mean goals pe", "Total goals b", "Goals on minu", "Goals on firs", "Goals on last", "Score opens b" };

size_t _identity = 0;

unordered_map<string, structTeam> teams;
unordered_map<size_t, string> teamsIds;
unordered_map<string, structPlayer> players;
deque<string> results;

string teamName[2];
size_t teamId[2],
	goals[2],
	timeFirstGoal[2],
	totalGoals = 0,
	stage = 0;
structTeam* pTeam[2];
structPlayer* pPlayer[2];

structTeam* getTeam(string name) {
	if (!teams.contains(name)) {
		teams[name] = { ++_identity };
		teamsIds[_identity] = name;
	}
	return &teams[name];
}

structPlayer* getPlayer(string name) {
	if (!players.contains(name))
		players[name] = { ++_identity };
	return &players[name];
}

structTeam* getTeamById(size_t id) {
	return &teams[teamsIds[id]];
}

void initNewGame() { //Start new game
	for (size_t i = 0; i < 2; i++) {
		teamId[i] = 0;
		goals[i] = 0;
		timeFirstGoal[i] = 0;
	}
};

string getTeamName(const string& line, size_t& start) {
	size_t index1, index2;
	index1 = line.find("\"", start);
	index2 = line.find("\"", index1 + 1);
	start = index2 + (index2 + 1 < line.size());
	return line.substr(index1 + 1, index2 - index1 - 1);
}

size_t getNumber(const string& line, size_t& start) {
	size_t index1 = 0,
		index2 = 0,
		i = start;
	while (i < line.size()) {
		if (index1 == 0 && isdigit(line[i]))
			index1 = i;
		if (index1 > 0 && !isdigit(line[i])) {
			index2 = i;
			break;
		}
		i++;
	}
	if (index2 == 0)
		index2 = line.size();
	i = stoi(line.substr(index1, index2 - index1 + 1));
	start = index2 + (index2 + 1 < line.size());
	return i;
}

void runRequests(const string& line) {
	size_t command = 0, i = 0, j = 0;
	string sTmp, res;
	structTeam* pTeam;
	structPlayer* pPlayer;

	sTmp = line.substr(0, 13);
	for (size_t i = 0; i < 8; i++) {
		if (sTmp == typeOfRequest[i]) {
			command = i;
			break;
		}
	}
	switch (command) {
	case 0:
		//Total goals for <Название команды> 
		i = 0;
		sTmp = getTeamName(line, i);
		pTeam = getTeam(sTmp);
		res = to_string(pTeam->goals);
		break;
	case 1:
		if (line.find("\"") != string::npos) {
			//Mean goals per game for <Название команды>
			sTmp = getTeamName(line, i);
			pTeam = getTeam(sTmp);
			res = to_string((double)pTeam->goals / pTeam->games);
		}
		else {
			//Mean goals per game by <Имя игрока> 
			sTmp = line.substr(23);
			pPlayer = getPlayer(sTmp);
			pTeam = getTeamById(pPlayer->idTeam);
			res = to_string((double)pPlayer->goals / pTeam->games);
		}
		break;
	case 2:
		//Total goals by <Имя игрока> 
		sTmp = line.substr(15);
		pPlayer = getPlayer(sTmp);
		res = to_string(pPlayer->goals);
		break;
	case 3:
		//Goals on minute <Минута> by <Имя игрока>
		i = 16;
		j = getNumber(line, i);
		sTmp = line.substr(i + 3);
		pPlayer = getPlayer(sTmp);
		res = to_string(pPlayer->times[j]);
		break;
	case 4:
		//Goals on first <T> minutes by <Имя игрока> — количество голов, забитых данным игроком на минутах с первой по T - ю включительно.
		i = 15;
		j = getNumber(line, i);
		sTmp = line.substr(i + 11);
		pPlayer = getPlayer(sTmp);
		i = 0;
		for (size_t k = 1; k <= j; k++) {
			i += pPlayer->times[k];
		}
		res = to_string(i);
		break;
	case 5:
		//Goals on last <T> minutes by <Имя игрока> — количество голов, забитых данным игроком на минутах с(91 - T) - й по 90 - ю включительно.
		i = 14;
		j = getNumber(line, i);
		sTmp = line.substr(i + 11);
		pPlayer = getPlayer(sTmp);
		i = 0;
		for (size_t k = (91 - j); k < 91; k++) {
			i += pPlayer->times[k];
		}
		res = to_string(i);
		break;
	case 6:
		if (line.find("\"") != string::npos) {
			//Score opens by <Название команды>
			i = 0;
			sTmp = getTeamName(line, i);
			pTeam = getTeam(sTmp);
			res = to_string(pTeam->firstGoals);
		}
		else {
			//Score opens by <Имя игрока>
			sTmp = line.substr(15);
			pPlayer = getPlayer(sTmp);
			res = to_string(pPlayer->firstGoals);
		}
		break;
	}
	results.push_back(res);
}

void parse(const string& line) {
	if (line == "") return;
	size_t i, j, iTmp,
		n = line.size();
	string sTmp = line.substr(0, 5);
	for (size_t i = 0; i < 4; i++) {
		if (sTmp == startOfRequest[i]) {
			runRequests(line);
			return;
		}
	}
	if (line[0] == '\"') { // Teams
		stage = 1;
		initNewGame();
		i = 0;
		teamName[0] = getTeamName(line, i);
		teamName[1] = getTeamName(line, i);
		goals[0] = getNumber(line, i);
		goals[1] = getNumber(line, i);
		for (size_t i = 0; i < 2; i++) {
			pTeam[i] = getTeam(teamName[i]);
			pTeam[i]->games++;
			pTeam[i]->goals += goals[i];
		}
		if (goals[0] == 0 && goals[1] == 0)
			stage = 0; // Finish game without winners
		if (goals[0] > 0)
			stage = 2; // Reading first goals first team
		else
			stage = 4; // Reading first goals second team
	}
	if (line[n - 1] == '\'') { // Goals
		i = 0;
		while (i != string::npos) {
			j = i;
			i = line.find(" ", i + 1);
		}
		sTmp = line.substr(0, j);
		structPlayer* tmpPlayer = getPlayer(sTmp);
		iTmp = getNumber(line, j);
		tmpPlayer->goals++;
		tmpPlayer->times[iTmp]++;
		switch (stage) {
		case 2: //First goal first team;
			pPlayer[0] = tmpPlayer;
			timeFirstGoal[0] = iTmp;
			stage = 3; // Other goals first team;
		case 3:
			goals[0]--;
			if (tmpPlayer->idTeam == 0)
				tmpPlayer->idTeam = pTeam[0]->id;
			if (goals[0] == 0) {
				if (goals[1] > 0)
					stage = 4; //Reading first goals second team
				else
					stage = 6; // Finish game
			}
			break;
		case 4: //First goal first team;
			pPlayer[1] = tmpPlayer;
			timeFirstGoal[1] = iTmp;
			stage = 5; // Other goals second team;
		case 5:
			goals[1]--;
			if (tmpPlayer->idTeam == 0)
				tmpPlayer->idTeam = pTeam[1]->id;
			if (goals[1] == 0)
				stage = 6; // Finish game
		}
		if (stage == 6) { // Define first goal
			int index = 0;
			if (timeFirstGoal[0] == 0)
				index = 1;
			else if (timeFirstGoal[1] == 0)
				index = 0;
			else
				index = (timeFirstGoal[0] > timeFirstGoal[1]);
			pPlayer[index]->firstGoals++;
			pTeam[index]->firstGoals++;
			stage = 0; // Ready for new game
		}
	}
}

int main() {
	string input;
	size_t step = 0;

	while (getline(cin, input))
		parse(input);
	for (const auto& line : results)
		cout << line << endl;
}
