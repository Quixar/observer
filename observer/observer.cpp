#include <iostream>
#include <vector>

using namespace std;

__interface IObserver {
public:
	virtual void Update(string status) = 0;
};

__interface IObservable {
public:
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

class RideRequest : public IObservable {
private:
	vector<IObserver*> observers;
	string status = "";

	void Notify() {
		for (auto observer : observers) {
			observer->Update(status);
		}
	}
public:
	void SetStatus(string status) {
		this->status = status;
		Notify();
	}

	string GetStatus() const {
		return status;
	}

	void Attach(IObserver* obs) {
		observers.push_back(obs);
	}

	void Detach(IObserver* obs) {
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
	}
};

class Monitoring : public IObserver {
private:
	IObservable* request;
public:
	Monitoring(IObservable* obj) {
		request = obj;
		obj->Attach(this);
	}
	void update(string status) {
		cout << "Status of request: " << status << "\n";
	}
};

class Driver {
public:
	void ExecutionRequest(RideRequest* ride_request) {
		ride_request->SetStatus("Accepted");
		ride_request->SetStatus("InProgress");
		ride_request->SetStatus("Completed");
	}
};

int main() {
	RideRequest ride_request;
	Monitoring monitoring;
	Driver driver;

	ride_request.Attach(&monitoring);

	cout << "Initial status: " << ride_request.GetStatus() << "\n";

	driver.ExecutionRequest(&ride_request);
}