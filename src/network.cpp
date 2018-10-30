#include "network.h"
#include <map>
#include <vector>
#include "random.h"

void Network::resize(const size_t& n) {
	values.resize(n);
	RNG.normal(values);
}

bool Network::add_link(const size_t& node_1, const size_t& node_2) {
	if(node_1 == node_2) {
		return false;
	} else if(node_1 > size() or node_2 >= size()) {
		return false;
	} else if((links.find(node_1))->second == node_2 and (links.find(node_2))->second == node_1) {
		return false;
	} else {
		links.insert({node_1, node_2});
		links.insert({node_2, node_1});
		return true;
	}
}

size_t Network::random_connect(const double& m) {
	links.erase(links.begin(), links.end());
	std::vector<size_t> tab_shuffled;
	for(size_t i(0); i < size(); ++i) {
		tab_shuffled.push_back(i);
	}
	size_t compteur(0);
	for(size_t i(0); i < size(); i++) {
		int j(RNG.poisson(m));
		RNG.shuffle(tab_shuffled);
		int k(0);
		int t(0);
		while((t < j) and (k < tab_shuffled.size())) {
			if(add_link(i, tab_shuffled[k])) {
				++compteur;
				++t;
			}
			++k;
		}
	}
	return compteur;
}

size_t Network::set_values(const std::vector<double>& vect) {
	values.clear();
	values = vect;
	return values.size();
}

size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t &_n) const {
	for (auto i : links) {
		if(i.first == _n) {
			return links.count(i.first);
		}
	}
}

double Network::value(const size_t &_n) const {
	return values[_n];
}

std::vector<double> Network::sorted_values() const {
	double tmp(0);
	std::vector<double> tab_tri;
	tab_tri = values;
	for(size_t taille(tab_tri.size()); taille != 0; taille--) {
		for(size_t i(0); i < taille; i++) {
			if(tab_tri[i] < tab_tri[i+1]) {
				tmp = tab_tri[i];
				tab_tri[i] = tab_tri[i+1];
				tab_tri[i+1] = tmp;
			}
		}
	}
	return tab_tri; 
}
    
std::vector<size_t> Network::neighbors(const size_t& node_index) const {
	std::vector<size_t> tab;
	for (auto i : links) {
		if(i.first == node_index) {
			tab.push_back(i.second);
		}
	}
	return tab;
}
