#ifndef SCHELLING_AGENT
#define SCHELLING_AGENT

#include "repast_hpc/AgentId.h"
#include "repast_hpc/SharedContext.h"
#include "repast_hpc/SharedDiscreteSpace.h"


class Agent{
	
private:
	repast::AgentId agentId;
	int agentType;
	bool isSatisfied;
	double threshold;
	
public:
	Agent(repast::AgentId id, int agentType, double threshold); //for init
	~Agent();
	Agent(repast::AgentId id, int agentType, bool isSatisfied); //for agent package
	
	/* Required Getters */
	virtual repast::AgentId& getId() { return agentId; }
	virtual const repast::AgentId& getId() const { return agentId; }
	
	/* Getters specific to this kind of Agent */
	int getType() { return agentType; }
	bool getSatisfiedStatus() { return isSatisfied; }
	
	/* Setter */
	void set(int currentRank, int newType, bool newSatisfiedStatus);

	/* Actions */
	void updateStatus(repast::SharedContext<Agent>* context,
			  repast::SharedDiscreteSpace<Agent, repast::StrictBorders, repast::SimpleAdder<Agent> >* space);
	void move(repast::SharedDiscreteSpace<Agent, repast::StrictBorders, repast::SimpleAdder<Agent> >* space);	
};

/* Serializable Agent Package */
struct AgentPackage {	
public:
	int	id;
	int	rank;
	int	type;
	int	currentRank;
	int agentType;
	bool isSatisfied ;
	
	/* Constructors */
	AgentPackage(); // For serialization
	AgentPackage(int _id, int _rank, int _type, int _currentRank, int _agentType, bool _isSatisfied);
	
	/* For archive packaging */
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & id;
		ar & rank;
		ar & type;
		ar & currentRank;
		ar & agentType;
		ar & isSatisfied;
	}
};

#endif