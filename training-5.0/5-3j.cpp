// https://contest.yandex.ru/contest/59541/problems/J/
#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <utility>

using namespace std;
size_t n, k;

class Device {
private:
	static size_t identity;
	static size_t countReady;
	size_t id = 0;
	size_t count = 1;
	bool isReady = false;
	set<size_t> downloads;
	vector<size_t> price;
	size_t whenReady = 0;
public:
	Device() : id(identity++), price(n, 0) {}
	const bool GetReady() { return isReady; }
	void SetId(size_t _id) { id = _id; }
	const size_t GetId() { return id; }
	const size_t GetCount() { return count; }
	const size_t GetCountReady() { return countReady; }
	const size_t GetPrice(size_t device) { return price[device]; }
	const size_t GetWhenReady() { return whenReady; }
	const bool CheckPackage(size_t package) { return downloads.contains(package); }
	void Download(size_t package, size_t deviceFrom, size_t step) {
		downloads.insert(package);
		count++;
		if (count == k) {
			isReady = true;
			whenReady = step;
			countReady++;
		}
		price[deviceFrom]++;
	}
};
size_t Device::identity = 0;
size_t Device::countReady = 2;

class Packages {
private:
	vector<size_t> countDownloadsForDevice;
	vector<vector<size_t>> relDevicePackage;
	set<pair<size_t, size_t>> orderedDownloads;
	vector<set<pair<size_t, size_t>>> orderedPackageDevice;
	deque<pair<Device*, size_t>> stack;

public:
	Packages() : countDownloadsForDevice(k, 0), relDevicePackage(n), orderedPackageDevice(k) {};

	void UpdatePackage(size_t package) {
		size_t count = countDownloadsForDevice[package];
		orderedDownloads.erase({ count, package });
		orderedDownloads.insert({ count + 1, package });
	}
	void UpdateDevices() {
		while (!stack.empty()) {
			Device device = *stack.front().first;
			size_t id = device.GetId();
			size_t count = stack.front().second;
			stack.pop_front();
			for (size_t package : relDevicePackage[id]) {
				size_t newCount = device.GetCount();
				orderedPackageDevice[package].erase({ count, id });
				orderedPackageDevice[package].insert({ newCount, id });
			}
		}
	}
	void Download(size_t package, Device& deviceTo, size_t deviceFrom, size_t step) {
		UpdatePackage(package);
		if (step == 1 && stack.empty() || step > 0)
			stack.push_back({ &deviceTo, deviceTo.GetCount() });
		deviceTo.Download(package, deviceFrom, step);
		relDevicePackage[deviceTo.GetId()].push_back(package);
		countDownloadsForDevice[package]++;
	}
	size_t GetPackage(Device& device) {
		size_t res = 0;
		for (auto e : orderedDownloads) {
			if (!device.CheckPackage(e.second)) {
				res = e.second;
				break;
			}
		}
		return res;
	}
	size_t GetDevice(size_t package) {
		return orderedPackageDevice[package].begin()->second;
	}
};

struct Query {
	size_t deviceTo;
	size_t package;
	bool IsEmpty() { return deviceTo == 0; }
	void Insert(size_t d, size_t p) { deviceTo = d; package = p; }
	void Clear() { deviceTo = 0; package = 0; }
};
bool IsBetter(vector<Device>& devices, size_t d0, size_t d1, size_t d2) {
	Device& D0 = devices[d0],
		D1 = devices[d1],
		D2 = devices[d2];
	size_t tmp1 = D0.GetPrice(d2),
		tmp2 = D0.GetPrice(d1); // Wrong order only for prices!
	if (tmp1 == tmp2) {
		tmp1 = D1.GetCount();
		tmp2 = D2.GetCount();
		if (tmp1 == tmp2) {
			tmp1 = d1;
			tmp2 = d2;
		}
	}
	return tmp1 > tmp2;
}

int main() {
	cin >> n >> k;
	n++; k++;
	vector<Device> devices(n);
	vector<Query> queries(n);
	Packages packages;
	size_t step = 1, package, deviceFrom;
	for (size_t i = 1; i < k; i++)
		packages.Download(i, devices[1], 0, step);
	while (devices[0].GetCountReady() <= n) {
		packages.UpdateDevices();
		// First stage
		for (size_t i = 1; i < n; i++) {
			if (devices[i].GetReady()) continue;
			package = packages.GetPackage(devices[i]);
			deviceFrom = packages.GetDevice(package);
			if (queries[deviceFrom].IsEmpty() ||
				IsBetter(devices, deviceFrom, queries[deviceFrom].deviceTo, i))
				queries[deviceFrom].Insert(i, package);
		}
		//Second stage 
		for (size_t i = 1; i < n; i++) {
			auto& _ = queries[i];
			if (_.IsEmpty()) continue;
			packages.Download(_.package, devices[_.deviceTo], i, step);
			_.Clear();
		}
		step++;
	}

	// Print results
	for (size_t i = 2; i < n; i++) {
		if (i > 2) cout << " ";
		cout << devices[i].GetWhenReady();
	}
	cout << endl;
}
