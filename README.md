对于线程的简单封装。
工作原理是：创建Active时需要传入逻辑处理回调；
Active::start会启动一个线程，通过Active:Send向线程投递数据；
逻辑层响应回调，这里只是用Active实现了个简单的工作线程，很方便做扩展。
具体示例可以参考main.cpp.这里可以快速封装一个异步日志库。
A simple wrapper for thread.
