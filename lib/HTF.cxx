/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <algorithm>
#include <sstream>
#include <stdio.h>
#include "HTF.h"

HFEnc::HTNode::HTNode(double prob, int val): _val(val), _prob(prob){};

/*
HFEnc::HTNode HFEnc::HTNode::getParent(){	
	return _parent;
}
*/

int HFEnc::HTNode::getVal() const{	
	return _val;
}

double HFEnc::HTNode::getProb() const{	
	return _prob;
}

double HFEnc::HTNode::setProb(double prob){
    return _prob = prob;
}

bool HFEnc::HTNode::nodeItrCmp(const nodeItr& lhs, const nodeItr& rhs){
    return lhs->_prob < rhs->_prob;
}

void HFEnc::appendNode(double prob){	
	nodes.push_back(HFEnc::HTNode(prob));
	nodeIts.push_back(nodes.end() - 1);
}

void HFEnc::setNode(std::vector<nodeItr>::iterator& it, int val){	
	(*it)->_val = val;
	(*it)->_parent = nodes.end() - 1;
	++it;
}

void HFEnc::build(){	
	auto beg = nodeIts.begin();
    size_t i  = syms;
    const size_t bSize = _bits.size();
    while(1){
        std::sort(beg, nodeIts.end(), HTNode::nodeItrCmp);
        double prob = 0;
        appendNode();
        for(size_t j = 0; j != std::min(i, bSize); ++j){
            printf("a %d\n", j);
            prob += (*beg)->getProb();
            setNode(beg, _bits[j]);
        }
		nodes.back().setProb(prob);
        if (i <= bSize){
            break;
        }
        i -= (bSize - 1);
        printf("b %d\n", i);
    }
}

//TODO: decouple code generation from trace
std::string HFEnc::trace(const HTNode& node) const{	
	nodeItr it = node._parent;
	std::stringstream code;
	code << node.getVal();
	while(it != nodes.end() - 1){	
		code << it->getVal();
		it = it->_parent;
	}
	std::string tmp = code.str();
	return std::string(tmp.rbegin(), tmp.rend());
}

const char* HFEnc::getCode(size_t ind) const{
    return trace(nodes[ind]).c_str();
}

std::vector<std::string> HFEnc::operator()(){
    build();
	std::vector<std::string> ret;
	ret.reserve(syms);
	for(size_t i = 0; i != syms; ++i){	
		ret.push_back(trace(nodes[i]));
	}
	return ret;
}
