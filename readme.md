# UE5蓝图使用Http
plugin中的插件是对UE Http的包装，以暴露接口给蓝图使用。  
没有用蓝图测试，不过用AngelScript脚本测试了下，理论上蓝图也是可用的：  
```
// 测试http
class ATest_HttpWrapper_AS : AActor
{
	UFUNCTION(CallInEditor)
	void Get()
	{
		auto Http = Cast<UHttpModuleWrapper>(NewObject(nullptr, UHttpModuleWrapper::StaticClass()));
		auto Request = Http.CreateRequest();
		Request.SetVerb("GET");
		Request.SetURL("https://www.baidu.com");
		Request.OnRequestProgress().BindUFunction(this, n"OnProgress");
		Request.OnProcessRequestComplete().BindUFunction(this, n"OnComplete");
        Log("get");
        Request.ProcessRequest();
	}

	UFUNCTION(CallInEditor)
	void Post()
	{
		auto Http = Cast<UHttpModuleWrapper>(NewObject(nullptr, UHttpModuleWrapper::StaticClass()));
		auto Request = Http.CreateRequest();
		Request.SetVerb("POST");
		Request.SetURL("https://httpbin.org/post");
		Request.SetHeader("Content-Type", "application/json");
		Request.SetContentAsString("{\"name\":\"axun\",\"gender\":1,\"title\":[\"the great lord\",\"six gad\",\"主=6\"]}");
		Request.OnRequestProgress().BindUFunction(this, n"OnProgress");
		Request.OnProcessRequestComplete().BindUFunction(this, n"OnComplete");
        Log("post");
        Request.ProcessRequest();
	}

	UFUNCTION()
	private void OnProgress(UHttpRequestWrapper Request, int BytesSent, int BytesReceived)
	{
		Log(f"sent:{BytesSent}, rec:{BytesReceived}");
	}

	UFUNCTION()
	private void OnComplete(UHttpRequestWrapper Request, UHttpResponseWrapper Response,
					bool bConnectedSuccessfully)
	{
		if (!bConnectedSuccessfully)
		{
			Log(f"connect error:{Request.GetStatus()}");
		}
		else
		{
			if (Response.GetResponseCode() == 200)
			{
                Log("http success");
                Log(f"{Response.GetContentAsString()}");
			}
			else
			{
                Log(f"http error:{Response.GetContentAsString()}");
			}
		}
	}
};
```