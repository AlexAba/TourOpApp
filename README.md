# Tour Operator App
### This is an application in which I show my knowledges of C++ and OOP.

Use Visual Studio to start up this application.
###### If you want to use GCC compiler the best way is to add all .cpp and .h files from TourOpAppVS to you directory and alter next things:
* in Voucher.cpp in methods: \
`void Voucher::ChangeTime(tm date);` \
`float Voucher::PriceRate();` \
use `{time_t now = time(0); tm * currentTime = new tm(); currentTime = gmtime(&now);}` instead of `{time_t now = time(0); tm currentTime = tm(); gmtime_s(&currentTime, &now);};`

* also amend `.` to `->`
