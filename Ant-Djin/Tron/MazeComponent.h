#pragma once
#include <Component.h>
#include <vector>
#include<glm/glm.hpp>


struct Node
{
	glm::ivec2 pos;

	Node* pLeftNode;
	Node* pRightNode;
	Node* pUpNode;
	Node* pDownNode;

};

struct Connection
{
	Node* first;
	Node* second;
};

class dae::GameObject;
class MazeComponent final : public dae::Component
{
public:
	MazeComponent(dae::GameObject* pGo);
	~MazeComponent();

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;


	void AddNode(Node* pNode);

	//get movement options given a current position


private:
	//nodes
	std::vector<Node*> m_pNodes;

	//connections (only for rendering purposes)
	std::vector<Connection> m_Connections;


};



