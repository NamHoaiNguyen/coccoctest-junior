#ifndef ALGO_H
#define ALGO_H

#include "../common/axis.h"
#include "../common/command_data.h"
#include "command.h"
#include "dimension_command.h"
#include "line_command.h"
#include "move_command.h"
#include "../parser/parser.h"

#include <assert.h>

class Algo : public State, public std::enable_shared_from_this<Algo> {
    private:
        /*Dependency injection
        Should be loose coupling instead of direct object like that*/
        std::shared_ptr<Parser> _parser;

        std::unordered_map<std::string, std::shared_ptr<Command>> _setCommand;

        std::vector<AxisAlgo> _result;

        DimensionAlgo _dimen;

        /*
        This variable is used to save the previous command and current axis
        Need to save the previous command because that we need to know which
        class hold information about current axis(MOVE or LINE)
        */
        DataCommand _prevData = {};

    public:
        explicit Algo(std::shared_ptr<Parser> parser) : _parser{parser} {

        }

        void handleRequest() override;

        void initialize();

        void execute();

        DataCommand getPrevData();

        void preprocessData();

        void setInfoForRender();

        DimensionAlgo getDimension();

        std::vector<AxisAlgo>& getAxisAlgo();

        friend class Renderer;
};

#endif