#include "Executor.h"
#include "Serializer.h"
#include "Deserializer.h"

/* Запускаем парсер введенной строки */

void Executor::startParsing(Strategy& strategy, History& history, Field& field)
{
	Command* com;
	
	com = parser.readInputCommand();

	system("cls");

	switch (com->Id)
	{
		case RESET:
		{
			strategy.reset();
		} break;

		case SET:
		{
			strategy.set(parser.getInt(com->argList), parser.getInt(com->argList));
		} break;

		case CLEAR:
		{
			strategy.clear(parser.getInt(com->argList), parser.getInt(com->argList));
		} break;

		case STEP:
		{
			strategy.step(parser.getInt(com->argList));
		} break;

		case BACK:
		{
			strategy.back(parser.getInt(com->argList));
		} break;

		case SAVE:
		{
			runSerializer(field, com);
		} break;

		case LOAD:
		{
			runDeserialiser(history, field, com);
		} break;
	}


}

/* Передаем управление методам сериалайзера/десериалайзера */

void Executor::runSerializer(Field& field, Command* com)
{
	Serializer out;
	out.writeToFile(com->argList->back(), field);
}

void Executor::runDeserialiser(History& history, Field& field, Command* com)
{
	Deserializer in;
	in.readFromFile(history, com->argList->back(), field);
}