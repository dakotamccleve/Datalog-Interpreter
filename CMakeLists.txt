cmake_minimum_required(VERSION 3.19.2)
project(cs236-project-5)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_5_main main.cpp ColonAutomaton.cpp ColonAutomaton.h ColonDashAutomaton.cpp ColonDashAutomaton.h Lexer.cpp Lexer.h Token.cpp Token.h MatcherAutomaton.cpp MatcherAutomaton.h IDAutomaton.cpp IDAutomaton.h StringAutomaton.cpp StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h DatalogProgram.cpp DatalogProgram.h Rule.cpp Rule.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Parser.cpp Parser.h Database.cpp Database.h Relation.cpp Relation.h Tuple.cpp Tuple.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h)