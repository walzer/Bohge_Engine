//////////////////////////////////////////////////////////////////////////////////////
//
//						The Bohge Engine License (BEL)
//
//	Copyright (c) 2011-2014 Peng Zhao
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in 
//	all copies or substantial portions of the Software. And the logo of 
//	Bohge Engine shall be displayed full screen for more than 3 seconds 
//	when the software is started. Copyright holders are allowed to develop 
//	game edit based on Bohge Engine, The edit must be released under the MIT 
//	open source license if it is going to be published. In no event shall 
//	copyright holders be prohibited from using any code of Bohge Engine 
//	to develop any other analogous game engines.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//
//////////////////////////////////////////////////////////////////////////////////////


#include "SoundResource.h"
#include "DecoderManager.h"
#include "Log.h"

namespace BohgeEngine
{
	//-------------------------------------------------------------------------------------------------------
	SoundResource::SoundResource( Decoder* decoder )
		:m_pDecoder(decoder ),
		m_nBufferSize(0),
		m_nCurrentBufferIndex(0),
		m_isDone(false)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	SoundResource::~SoundResource(void)
	{
		DecoderManager::Instance()->UnloadSoundDecoder( m_pDecoder );
	}
	//-------------------------------------------------------------------------------------------------------
	void SoundResource::FlushBufferData()
	{
		Decoder::BufferChunk buffer = m_pDecoder->GetBufferChunk(m_nCurrentBufferIndex);
		m_nCurrentBufferIndex = buffer.GetNextIndex();
		//DEBUGLOG("next index %d\n", m_nCurrentBufferIndex );
		m_nBufferSize = buffer.GetSize();
		m_BufferAddress = buffer.GetBuffer();
		m_isDone = buffer.isDone();
		RequestDecode();//要求下一段数据
		//DEBUGLOG("m_isDone %s\n", m_isDone ? "true" : "false" );
	}

}