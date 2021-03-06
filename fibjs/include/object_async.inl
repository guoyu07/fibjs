#define ASYNC_STATIC0(cls, m) \
	static result_t ac_##m() { \
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	_t ac(NULL); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m() { \
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	_t ac(NULL); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m(v8::Local<v8::Function> cb) { \
	class _t: public AsyncCallBack { \
	public: \
		_t(v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
	}; \
	_t* ac = new _t(cb); \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER0(cls, m) \
	result_t ac_##m() { \
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[0])->m( \
				this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m() { \
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[0])->m( \
				this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m(v8::Local<v8::Function> cb) { \
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
	}; \
	_t* ac = new _t(this, cb); \
	result_t hr = m(NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE1(cls, m, T0) \
	static result_t ac_##m( \
		T0& v0) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0& v0) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T0 retVal; \
	private: \
	}; \
	_t* ac = new _t(cb); \
	result_t hr = m(ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE1(cls, m, T0) \
	result_t ac_##m( \
		T0& v0) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[1])->m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0& v0) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[1])->m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T0 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
	}; \
	_t* ac = new _t(this, cb); \
	result_t hr = m(ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC1(cls, m, T0) \
	static result_t ac_##m( \
		T0 v0) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
	}; \
	_t* ac = new _t(v0, cb); \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER1(cls, m, T0) \
	result_t ac_##m( \
		T0 v0) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[1])->m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[1])->m( \
				*(T0*) args[0], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
	}; \
	_t* ac = new _t(this, v0, cb); \
	result_t hr = m(v0, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE2(cls, m, T0, T1) \
	static result_t ac_##m( \
		T0 v0, T1& v1) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1& v1) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T1 retVal; \
	private: \
		_at<T0> m_v0; \
	}; \
	_t* ac = new _t(v0, cb); \
	result_t hr = m(v0, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE2(cls, m, T0, T1) \
	result_t ac_##m( \
		T0 v0, T1& v1) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[2])->m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1& v1) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[2])->m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T1 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
	}; \
	_t* ac = new _t(this, v0, cb); \
	result_t hr = m(v0, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC2(cls, m, T0, T1) \
	static result_t ac_##m( \
		T0 v0, T1 v1) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
	}; \
	_t* ac = new _t(v0, v1, cb); \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER2(cls, m, T0, T1) \
	result_t ac_##m( \
		T0 v0, T1 v1) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[2])->m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[2])->m( \
				*(T0*) args[0], *(T1*) args[1], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
	}; \
	_t* ac = new _t(this, v0, v1, cb); \
	result_t hr = m(v0, v1, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE3(cls, m, T0, T1, T2) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2& v2) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2& v2) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T2 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
	}; \
	_t* ac = new _t(v0, v1, cb); \
	result_t hr = m(v0, v1, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE3(cls, m, T0, T1, T2) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2& v2) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[3])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2& v2) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[3])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T2 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
	}; \
	_t* ac = new _t(this, v0, v1, cb); \
	result_t hr = m(v0, v1, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC3(cls, m, T0, T1, T2) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
	}; \
	_t* ac = new _t(v0, v1, v2, cb); \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER3(cls, m, T0, T1, T2) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[3])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[3])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, cb); \
	result_t hr = m(v0, v1, v2, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE4(cls, m, T0, T1, T2, T3) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3& v3) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3& v3) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T3 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
	}; \
	_t* ac = new _t(v0, v1, v2, cb); \
	result_t hr = m(v0, v1, v2, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE4(cls, m, T0, T1, T2, T3) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3& v3) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[4])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3& v3) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[4])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T3 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, cb); \
	result_t hr = m(v0, v1, v2, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC4(cls, m, T0, T1, T2, T3) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, cb); \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER4(cls, m, T0, T1, T2, T3) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[4])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[4])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, cb); \
	result_t hr = m(v0, v1, v2, v3, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE5(cls, m, T0, T1, T2, T3, T4) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4& v4) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4& v4) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T4 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, cb); \
	result_t hr = m(v0, v1, v2, v3, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE5(cls, m, T0, T1, T2, T3, T4) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4& v4) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[5])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4& v4) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[5])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T4 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, cb); \
	result_t hr = m(v0, v1, v2, v3, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC5(cls, m, T0, T1, T2, T3, T4) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER5(cls, m, T0, T1, T2, T3, T4) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[5])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[5])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE6(cls, m, T0, T1, T2, T3, T4, T5) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5& v5) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5& v5) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T5 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE6(cls, m, T0, T1, T2, T3, T4, T5) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5& v5) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[6])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5& v5) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[6])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T5 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC6(cls, m, T0, T1, T2, T3, T4, T5) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER6(cls, m, T0, T1, T2, T3, T4, T5) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[6])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[6])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE7(cls, m, T0, T1, T2, T3, T4, T5, T6) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6& v6) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6& v6) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T6 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE7(cls, m, T0, T1, T2, T3, T4, T5, T6) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6& v6) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[7])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6& v6) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[7])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T6 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC7(cls, m, T0, T1, T2, T3, T4, T5, T6) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER7(cls, m, T0, T1, T2, T3, T4, T5, T6) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[7])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[7])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE8(cls, m, T0, T1, T2, T3, T4, T5, T6, T7) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7& v7) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7& v7) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T7 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE8(cls, m, T0, T1, T2, T3, T4, T5, T6, T7) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7& v7) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[8])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7& v7) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[8])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T7 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC8(cls, m, T0, T1, T2, T3, T4, T5, T6, T7) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, v7, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER8(cls, m, T0, T1, T2, T3, T4, T5, T6, T7) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[8])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[8])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, v7, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE9(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8& v8) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8& v8) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T8 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, v7, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE9(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8& v8) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[9])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8& v8) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[9])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T8 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, v7, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATIC9(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7), m_v8(v8) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), m_v8.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
		_at<T8> m_v8; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, v7, v8, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBER9(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[9])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[9])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7), m_v8(v8) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), m_v8.value(), this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
		_at<T8> m_v8; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, v7, v8, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_STATICVALUE10(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) \
	static result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9& v9) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], *(T9*) args[9], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9& v9) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = cls::m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], *(T9*) args[9], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	static void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7), m_v8(v8) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = cls::m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), m_v8.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T9 retVal; \
	private: \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
		_at<T8> m_v8; \
	}; \
	_t* ac = new _t(v0, v1, v2, v3, v4, v5, v6, v7, v8, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}

#define ASYNC_MEMBERVALUE10(cls, m, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) \
	result_t ac_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9& v9) {\
	class _t : public AsyncCall { public: \
		_t(void ** a) : AsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[10])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], *(T9*) args[9], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	result_t cc_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9& v9) {\
	class _t : public CAsyncCall { public: \
		_t(void ** a) : CAsyncCall(a) {} \
		virtual void invoke() { \
			result_t hr = ((cls*)args[10])->m( \
				*(T0*) args[0], *(T1*) args[1], *(T2*) args[2], *(T3*) args[3], *(T4*) args[4], *(T5*) args[5], *(T6*) args[6], *(T7*) args[7], *(T8*) args[8], *(T9*) args[9], this); \
			if(hr != CALL_E_PENDDING)post(hr); } }; \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)return hr; \
	void* args[] = {&v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, this}; \
	_t ac(args); \
	if(hr != CALL_E_NOSYNC){ac.async(hr); return ac.wait();} \
	else return ac.async_wait(); \
	} \
	void acb_##m( \
		T0 v0, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, v8::Local<v8::Function> cb) {\
	class _t: public AsyncCallBack { \
	public: \
		_t(cls* pThis, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, v8::Local<v8::Function> cb) : \
			AsyncCallBack(cb), m_pThis(pThis), m_v0(v0), m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4), m_v5(v5), m_v6(v6), m_v7(v7), m_v8(v8) \
		{} \
		virtual void invoke() \
		{ \
			result_t hr = m_pThis->m(m_v0.value(), m_v1.value(), m_v2.value(), m_v3.value(), m_v4.value(), m_v5.value(), m_v6.value(), m_v7.value(), m_v8.value(), retVal, this); \
			if (hr != CALL_E_PENDDING)post(hr); \
		} \
    virtual v8::Local<v8::Value> getValue() \
    {   return GetReturnValue(m_isolate->m_isolate, retVal); } \
	public: \
		T9 retVal; \
	private: \
		obj_ptr<cls> m_pThis; \
		_at<T0> m_v0; \
		_at<T1> m_v1; \
		_at<T2> m_v2; \
		_at<T3> m_v3; \
		_at<T4> m_v4; \
		_at<T5> m_v5; \
		_at<T6> m_v6; \
		_at<T7> m_v7; \
		_at<T8> m_v8; \
	}; \
	_t* ac = new _t(this, v0, v1, v2, v3, v4, v5, v6, v7, v8, cb); \
	result_t hr = m(v0, v1, v2, v3, v4, v5, v6, v7, v8, ac->retVal, NULL); \
	if(hr != CALL_E_NOSYNC && hr != CALL_E_LONGSYNC && hr != CALL_E_GUICALL)ac->post(hr); \
	else ac->async(hr); \
	}
