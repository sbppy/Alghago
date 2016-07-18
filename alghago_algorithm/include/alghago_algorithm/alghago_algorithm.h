#include <vector>
#include <eigen3/Eigen/Dense>

#include "common_math.h"

using namespace std;
using namespace Eigen;
using namespace SuhanMath;


// Here, you can add some new probablity gains:)
const double kThreaten = 0.4;
const double kThreating = 0.6;


struct AlghagoNode
{
    /**
     * @brief coordinate coordinate of node \n
     * (0) = x, (1) = y
     */
    Vector2d coordinate;

    /**
     * @brief rectAvailable \n
     * (0,0) = x1, (0,1) = y1, (1,0) = x2, (1,1) = y2
     */
    Matrix2d rectAvailable;

    /**
     * @brief rectDisturbance \n
     * (0,0) = x1, (0,1) = y1, (1,0) = x2, (1,1) = y2
     */
    Matrix2d rectDisturbance;

    // Here, you can add some new probablity :)
    vector<double> pThreaten;
    vector<double> pThreating;


    vector<double> pTotal;
};


class AlghagoAlgorithm
{
    // Sum of all gains should be 1


    enum EDGE_POINTS {LEFT_TOP, RIGHT_TOP, LEFT_BOT, RIGHT_BOT};

    const double BOARD_WIDTH;
    const double BOARD_HEIGHT;

    int shootIndex;
    int targetIndex;

    vector<AlghagoNode> robotNodes;
    vector<AlghagoNode> userNodes;


    Vector2d boardVertics[4];

public:
    AlghagoAlgorithm() { _initialize(); }

    void updateNodes(vector<AlghagoNode> &updateRobotNodes,
                     vector<AlghagoNode> &updateUserNodes)
    {
        robotNodes = updateRobotNodes;
        userNodes = updateUserNodes;
    }

    void compute()
    {
        _compute_threating();
        _compute_threated();
        _choose_node();
    }
    void write(Vector2d &shoot, Vector2d &target)
    {
        shoot = robotNodes[shootIndex].coordinate;
        target = userNodes[targetIndex].coordinate;
    }


private:
    void _initialize();
    void _update_variables();
    void _compute_threating();

    bool _check_in_range(const AlghagoNode &node, const Matrix2d &range);
    bool _check_on_line(const AlghagoNode &node, double rho, double theta, double r, double & rho_hat);


    void _get_line_equation(const AlghagoNode& node1, const AlghagoNode& node2, double& rho, double& theta);
    void _get_line_intersection(const AlghagoNode& node1, const AlghagoNode& node2, Vector2d& intersection);
    void _get_rect_available(AlghagoNode& robotNode, const AlghagoNode& userNode);
    void _get_rect_disturbance(AlghagoNode& robotNode, const AlghagoNode& userNode);

    void _compute_threated();
    void _choose_node();
};
