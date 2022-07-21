#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

	class Checker {
		
		private:
			int xCoord;
			int yCoord;
			char color;
			bool isPlaceHolder;
			bool isKing;
			
		public:
			Checker() {
				
			}
			
			Checker(char color) {
				this -> color = color;
				this -> xCoord = 0;
				this -> yCoord = 0;
				this -> isPlaceHolder = false;
				this -> isKing = false;
			}
			
			Checker(bool isPlaceHolder) {
				this -> color = ' ';
				this -> isPlaceHolder = true;
				this -> xCoord = 0;
				this -> yCoord = 0;
				this -> isKing = false;
			}
			
			void set_xCoord(int xCoord);
			int get_xCoord();
			
			void set_yCoord(int yCoord);
			int get_yCoord();
			
			void set_color(char color);
			char get_color();
			
			void set_placeHolder(bool isPlaceHolder);
			bool is_placeHolder();
			
			void set_king();
			bool is_king();
	};
	
	
	
	void Checker::set_xCoord(int xCoord) {
		this -> xCoord = xCoord;
	}
	
	
	
	int Checker::get_xCoord() {
		return xCoord;
	}
	
	
	
	void Checker::set_yCoord(int yCoord) {
		this -> yCoord = yCoord;
	}
	
	
	
	int Checker::get_yCoord() {
		return yCoord;
	}
	
	
	
	void Checker::set_color(char color) {
		this -> color = color;
	}
	
	
	
	char Checker::get_color() {
		return color;
	}
	
	
	
	void Checker::set_placeHolder(bool isPlaceHolder) {
		this -> isPlaceHolder = isPlaceHolder;
	}
	
	
	
	bool Checker::is_placeHolder() {
		return isPlaceHolder;
	}
	
	
	
	void Checker::set_king() {
		this -> isKing = true;
	}
	
	
	
	bool Checker::is_king() {
		return isKing;
	}
	
	
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
	
	
	struct PossibleMove {
	
		Checker checker;
		int xCoord;
		int yCoord;
		int jumpY;
		int jumpX;
		bool isJump;
		
		PossibleMove(Checker checker, int yCoord, int xCoord) {
			this -> checker = checker;
			this -> yCoord = yCoord;
			this -> xCoord = xCoord;
			this -> isJump = false;
		}
		
		PossibleMove(Checker checker, int yCoord, int xCoord, int jumpY, int jumpX) {
			this -> checker = checker;
			this -> yCoord = yCoord;
			this -> xCoord = xCoord;
			this -> jumpY = jumpY;
			this -> jumpX = jumpX;
			this -> isJump = true;
		}
	};
	
	
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
	
	
	class Player {
	
		private:
			int numWins;
			char color;
			int numCheckers;
			
		public:
			Player() {
				
			}
			
			Player(char color) {
				this -> color = color;
				this -> numWins = 0;
				this -> numCheckers = 12;
			}
			
			void add_win();
			int get_numWins();
			
			char get_color();
			
			void remove_checker();
			int get_numCheckers();
			
			Player switchPlayers(Player playerOne, Player playerTwo);
	};
	
	
	
	void Player::add_win() {
		this -> numWins += 1;
	}
	
	
	
	int Player::get_numWins() {
		return numWins;
	}
	
	
	
	char Player::get_color() {
		return color;
	}
	
	
	
	void Player::remove_checker() {
		this -> numCheckers -= 1;
	}
	
	
	
	int Player::get_numCheckers() {
		return numCheckers;
	}
	
	
	
	Player Player::switchPlayers(Player playerOne, Player playerTwo) {
	
		if(this -> color == 'b') {
			return playerTwo;
		} else {
			return playerOne;
		}
	}
	
	
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
	
	
	class Board {
		
		private:
			Checker board[8][8];
			
		public:
			std::vector<PossibleMove> possibleMoves;
			
			Board() {
				populateBoard(new Checker('r'), new Checker('b'), new Checker(true));
			}
			
			void populateBoard(Checker *redChecker, Checker *blackChecker, Checker *placeHolder);
			void printBoard();
			void checkMove(char color);
			int get_xOrigin(int i);
			int get_yOrigin(int i);
			int get_xDest(int i);
			int get_yDest(int i);
			void moveChecker(Player &player, int choice);
			void removeChecker(Player &player, int y, int x);
			void kingMeCheck(int y, int x);
	};
	
	
	
	void Board::populateBoard(Checker *redChecker, Checker *blackChecker, Checker *placeHolder) {
		
		for(int y = 0; y < 8; y++) {		
			for(int x = 0; x < 8; x++) {
				if(y < 3) {
					if(y % 2 == 0 && x % 2 != 0) {
						board[y][x] = *redChecker;
						board[y][x].set_yCoord(y);
						board[y][x].set_xCoord(x);
					}
					
					else if(y % 2 != 0 && x % 2 == 0) {
						board[y][x] = *redChecker;
						board[y][x].set_yCoord(y);
						board[y][x].set_xCoord(x);
					}
					
					else {
						board[y][x] = *placeHolder;
					}
				} 
				
				else if(y > 4) {
					if(y % 2 != 0 && x % 2 == 0) {
						board[y][x] = *blackChecker;
						board[y][x].set_yCoord(y);
						board[y][x].set_xCoord(x);
					}
					
					else if(y % 2 == 0 && x % 2 != 0) {
						board[y][x] = *blackChecker;
						board[y][x].set_yCoord(y);
						board[y][x].set_xCoord(x);
					}
					
					else {
						board[y][x] = *placeHolder;
					}
				}
				
				else {
					board[y][x] = *placeHolder;
				}
			}
		}
	}
	
	
	
	void Board::printBoard() {
		
		std::cout << std::endl << " ";
		
		for(int x = 0; x < 8; x++) {
			std::cout << std::setw(8) << x + 1;
		}
		
		std::cout << std::endl;
		
		for(int y = 0; y < 8; y++) {
			std::cout << "    ";
			
			for(int x = 0; x < 8; x++) {
				if(y == 0) {
					std::cout << " " << char(196) << " " << char(196) << " " << char(196) << " " << char(196);
				} else {
					std::cout << "|" << char(196) << " " << char(196) << " " << char(196) << " " << char(196);
					
					if(x == 7) {
						std::cout << "|";
					}
				}
			}
			
			std::cout << std::endl;
			
			for(int i = 0; i < 3; i++) {
				std::cout << "  ";
				
				if(i % 2 != 0) {
					std::cout << y + 1 << std::setw(2) << "|";
				} else {
					std::cout << std::setw(3) << "|";
				}
				
				for(int x = 0; x < 8; x++) {
					if(i % 2 != 0) {
						std::cout << "   " << board[y][x].get_color() << std::setw(4) << "|";
					} else {
						std::cout << std::setw(8) << "|";
					}
				}
				
				std::cout << std::endl;
			}
		}
		
		std::cout << "    ";
		
		for(int x = 0; x < 8; x++) {
			std::cout << " " << char(196) << " " << char(196) << " " << char(196) << " " << char(196);
		}
	}
	
	
	
	void Board::checkMove(char color) { 
	
		for(int y = 0; y < 8; y++) {
			for(int x = 0; x < 8; x++) {
				if(board[y][x].get_color() == color) {
					if(board[y][x].get_color() == 'r') {
						if(board[y][x].is_king()) {
							if(board[y][x].get_yCoord() > 0) {
								if(board[y][x].get_xCoord() < 7 && board[y - 1][x + 1].is_placeHolder()) {
									possibleMoves.push_back(PossibleMove(board[y][x], y - 1, x + 1));
								}
								
								if(board[y][x].get_xCoord() > 0 && board[y - 1][x - 1].is_placeHolder()) {
									possibleMoves.push_back(PossibleMove(board[y][x], y - 1, x - 1));
								}
							}
							
							if(board[y][x].get_yCoord() > 1) {
								if(board[y][x].get_xCoord() < 6 && board[y - 2][x + 2].is_placeHolder() && board[y - 1][x + 1].get_color() == 'b') {
									possibleMoves.push_back(PossibleMove(board[y][x], y - 2, x + 2, y - 1, x + 1));
								}
								
								if(board[y][x].get_xCoord() > 1 && board[y - 2][x - 2].is_placeHolder() && board[y - 1][x - 1].get_color() == 'b') {
									possibleMoves.push_back(PossibleMove(board[y][x], y - 2, x - 2, y - 1, x - 1));
								}
							}
						}
						
						if(board[y][x].get_yCoord() < 7) {
							if(board[y][x].get_xCoord() < 7 && board[y + 1][x + 1].is_placeHolder()) {
								possibleMoves.push_back(PossibleMove(board[y][x], y + 1, x + 1));
							}
							
							if(board[y][x].get_xCoord() > 0 && board[y + 1][x - 1].is_placeHolder()) {
								possibleMoves.push_back(PossibleMove(board[y][x], y + 1, x - 1));
							}
						}
						
						if(board[y][x].get_yCoord() < 6) {
							if(board[y][x].get_xCoord() < 6 && board[y + 2][x + 2].is_placeHolder() && board[y + 1][x + 1].get_color() == 'b') {
								possibleMoves.push_back(PossibleMove(board[y][x], y + 2, x + 2, y + 1, x + 1));
							}
							
							if(board[y][x].get_xCoord() > 1 && board[y + 2][x - 2].is_placeHolder() && board[y + 1][x - 1].get_color() == 'b') {
								possibleMoves.push_back(PossibleMove(board[y][x], y + 2, x - 2, y + 1, x - 1));
							}	
						}	
					}
				
					else if(board[y][x].get_color() == 'b') {
						if(board[y][x].is_king()) {
							if(board[y][x].get_yCoord() < 7) {
								if(board[y][x].get_xCoord() < 7 && board[y + 1][x + 1].is_placeHolder()) {
									possibleMoves.push_back(PossibleMove(board[y][x], y + 1, x + 1));
								}
								
								if(board[y][x].get_xCoord() > 0 && board[y + 1][x - 1].is_placeHolder()) {
									possibleMoves.push_back(PossibleMove(board[y][x], y + 1, x - 1));
								}
							}
						
							if(board[y][x].get_yCoord() < 6) {
								if(board[y][x].get_xCoord() < 6 && board[y + 2][x + 2].is_placeHolder() && board[y + 1][x + 1].get_color() == 'r') {
									possibleMoves.push_back(PossibleMove(board[y][x], y + 2, x + 2, y + 1, x + 1));
								}
								
								if(board[y][x].get_xCoord() > 1 && board[y + 2][x - 2].is_placeHolder() && board[y + 1][x - 1].get_color() == 'r') {
									possibleMoves.push_back(PossibleMove(board[y][x], y + 2, x - 2, y + 1, x - 1));
								}	
							}
						}
						
						if(board[y][x].get_yCoord() > 0) {
							if(board[y][x].get_xCoord() < 7 && board[y - 1][x + 1].is_placeHolder()) {
								possibleMoves.push_back(PossibleMove(board[y][x], y - 1, x + 1));
							}
							
							if(board[y][x].get_xCoord() > 0 && board[y - 1][x - 1].is_placeHolder()) {
								possibleMoves.push_back(PossibleMove(board[y][x], y - 1, x - 1));
							}
						}
						
						if(board[y][x].get_yCoord() > 1) {
							if(board[y][x].get_xCoord() < 6 && board[y - 2][x + 2].is_placeHolder() && board[y - 1][x + 1].get_color() == 'r') {
								possibleMoves.push_back(PossibleMove(board[y][x], y - 2, x + 2, y - 1, x + 1));
							}
							
							if(board[y][x].get_xCoord() > 1 && board[y - 2][x - 2].is_placeHolder() && board[y - 1][x - 1].get_color() == 'r') {
								possibleMoves.push_back(PossibleMove(board[y][x], y - 2, x - 2, y - 1, x - 1));
							}
						}
					}
				}
			}
		}
	}
	
	
	
	int Board::get_xOrigin(int i) {
		
		return possibleMoves[i].checker.get_xCoord() + 1;
	}
	
	
	
	int Board::get_yOrigin(int i) {
		
		return possibleMoves[i].checker.get_yCoord() + 1;
	}
	
	
	
	int Board::get_xDest(int i) {
		
		return possibleMoves[i].xCoord + 1;
	}
	
	
	
	int Board::get_yDest(int i) {
		
		return possibleMoves[i].yCoord + 1;
	}
	
	
	
	void Board::moveChecker(Player &player, int choice) {
		
		int yOrigin = possibleMoves[choice - 1].checker.get_yCoord();
		int xOrigin = possibleMoves[choice - 1].checker.get_xCoord();
		
		int xDest = possibleMoves[choice - 1].xCoord;
		int yDest = possibleMoves[choice - 1].yCoord;
		
		int jumpY = possibleMoves[choice - 1].jumpY;
		int jumpX = possibleMoves[choice - 1].jumpX;
		
		std::swap(board[yOrigin][xOrigin], board[yDest][xDest]);
		
		board[yDest][xDest].set_yCoord(yDest);
		board[yDest][xDest].set_xCoord(xDest);
		
		if(possibleMoves[choice - 1].isJump) {
			removeChecker(player, jumpY, jumpX);
		}
		
		kingMeCheck(yDest, xDest);
	}
	
	

	void Board::removeChecker(Player &player, int y, int x) {
		
		board[y][x] = new Checker(true);
		
		player.remove_checker();
	}
	

	
	void Board::kingMeCheck(int y, int x) {
		
		if(board[y][x].get_yCoord() == 0 && board[y][x].get_color() == 'b' || board[y][x].get_yCoord() == 7 && board[y][x].get_color() == 'r') {
			board[y][x].set_king();
		}
	}



	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
	
	
	class Menu {
		
		private:
			void printMoveNum(int i, int x);
			
		public:
			Menu() {
				
			}
			
			void makeMove(Player player, Board &board);
			void printMenu(Player player, Board board);
			bool validInput(Board board, int choice);
	};
	
	
		
	void Menu::makeMove(Player player, Board &board) {
		
		int choice;
		
		do {
			printMenu(player, board);
			
			std::cout << std::setw(25) << "Choose your move: ";
			std::cin >> choice;
			
			if(!validInput(board, choice)) {
				std::cout << std::setw(28) << std::endl << "Error: Invalid input." << std::endl << std::endl;
				
				std::cout << std::setw(33) << "Press ENTER to continue...";
				
				std::cin.sync(); 
				std::cin.get();
	  			
				system("CLS");
				
				board.printBoard();
			}
		} while(!validInput(board, choice));
		
		board.moveChecker(player, choice);
		
		board.possibleMoves.clear();
		
		system("CLS");
	}
	
	
	
	void Menu::printMenu(Player player, Board board) {
		
		std::cout << std::endl << std::endl << std::endl << std::setw(48) << "=======================" << std::endl << std::setw(45);
		
		if(player.get_color() == 'b') {
			std::cout << "Player One's Turn";
		} else {
			std::cout << "Player Two's Turn";
		}
		
		std::cout << std::endl << std::setw(48) << "=======================" << std::endl;
		
		std::cout << std::endl << std::setw(48) << "=======================" << std::endl << std::setw(46) << "Possible Moves List" << std::endl << std::setw(48) << "=======================" << std::endl << std::endl;
		
		for(int i = 0; i < board.possibleMoves.size(); i++) {
			if(i % 2 == 0) {
				if(i != board.possibleMoves.size() - 1) {
					std::cout << std::setw(35) << "============================" << std::setw(31) << "============================" << std::endl;
				} else {
					std::cout << std::setw(35) << "============================" << std::endl;
				}
				
				if(i != board.possibleMoves.size() - 1) {
					printMoveNum(i + 1, 8);
					
					std::cout << " x: " << board.get_xOrigin(i) << ", y: " << board.get_yOrigin(i) << " -> x: " << board.get_xDest(i) << ", y: " << board.get_yDest(i);
				} else {
					printMoveNum(i + 1, 8);
					
					std::cout << " x: " << board.get_xOrigin(i) << ", y: " << board.get_yOrigin(i) << " -> x: " << board.get_xDest(i) << ", y: " << board.get_yDest(i) << std::endl;
					std::cout << std::setw(35) << "============================" << std::endl;
				}
			} else {
				printMoveNum(i + 1, 4);
					
				std::cout << " x: " << board.get_xOrigin(i) << ", y: " << board.get_yOrigin(i) << " -> x: " << board.get_xDest(i) << ", y: " << board.get_yDest(i) << std::endl;
				std::cout << std::setw(35) << "============================" << std::setw(31) << "============================" << std::endl;
			}
		}
		
		std::cout << std::endl << std::endl;
	}
	
	
	
	void Menu::printMoveNum(int i, int x) {
		
		if(i < 10) {
			std::cout << std::setw(x);
			std::cout << "0" << i << ")";
		} else {
			std::cout << std::setw(x + 1);
			std::cout << i << ")";
		}
	}
	
	
	
	bool Menu::validInput(Board board, int choice) {
		
		if(choice > 0 && choice <= board.possibleMoves.size() && !std::cin.fail()) {
			return true;
		} else {
			if(std::cin.fail()) {
				std::cin.clear();
			}
			
			return false;
		}
	}



	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	


	int main() {
		
		Board board;
		Player playerOne('b');
		Player playerTwo('r');
		Player currPlayer('b');
		Menu menu;
		
		while(playerOne.get_numCheckers() > 0 && playerTwo.get_numCheckers() > 0) {
			board.checkMove(currPlayer.get_color());
			
			if(board.possibleMoves.size() > 0) {
				board.printBoard();
				
				menu.makeMove(currPlayer, board);
				
				currPlayer = currPlayer.switchPlayers(playerOne, playerTwo);
			} else {
				if(currPlayer.get_color() == 'b') {
					playerTwo.add_win();
				} else {
					playerOne.add_win();
				}
				
				break;
			}
		}
		
		return 0;
	}
