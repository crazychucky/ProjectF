#include "WaterFilter/ShaderNode.h"

ShaderNode::ShaderNode()
{

}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
	ShaderNode* shader = new ShaderNode();
	if(shader && shader->initWithVertex(vert,frag))
	{
		shader->autorelease();
		return shader;
	}

	CC_SAFE_DELETE(shader);
	return NULL;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
	CCGLProgram* shader = new CCGLProgram();  
	shader->initWithVertexShaderFilename(vert, frag);   //������ɫ������  

	//��attribute����  
	shader->addAttribute("a_position", 0);  
	shader->addAttribute("a_color", 1);  
	shader->link();  

	//��ȡattribute������ʶ  
	m_attributeColor = glGetAttribLocation(shader->getProgram(), "a_color");  
	m_attributePosition = glGetAttribLocation(  
		shader->getProgram(), "a_position");  
	shader->updateUniforms();  

	//��ȡuniform������ʶ  
	m_uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");  
	m_uniformTime = glGetUniformLocation(shader->getProgram(), "time");  
	m_uniformTex0 = glGetUniformLocation(shader->getProgram(), "tex0");  

	//ʹ����ɫ������  
	this->setShaderProgram(shader);  
	shader->release();  
}

void ShaderNode::setColor(ccColor4F newColor)
{
	color[0] = newColor.r;
	color[1] = newColor.g;
	color[2] = newColor.b;
	color[3] = newColor.a;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{
	loadShaderVertex(vert,frag);
	m_texture = CCTextureCache::sharedTextureCache()->addImage("HelloWorld.png")->getName();

	setContentSize(CCSizeMake(1024,768));
	setColor(ccc4f(0.5,0.5,1,1));
	m_time = 0;
	scheduleUpdate();
	return true;
}

void ShaderNode::update(float dt)
{
	m_time += dt;
}

void ShaderNode::setContentSize(const CCSize& var)
{
	CCNode::setContentSize(var);
	m_resolution = vertex2(getContentSize().width,getContentSize().height);
	m_center.x = m_resolution.x/2;
	m_center.y = m_resolution.y/2;
}

void ShaderNode::draw()
{
	CC_NODE_DRAW_SETUP();  

	//����uniform����  
	CCGLProgram* shader = getShaderProgram();  
	shader->setUniformLocationWith2f(m_uniformResolution, m_resolution.x,  
		m_resolution.y);
	shader->setUniformLocationWith1i(m_uniformTex0, 0); 
	glUniform1f(m_uniformTime, m_time);

	//��ȡattribute����  
	CCSize size = this->getContentSize();  
	float w = size.width;  
	float h = size.height;  

	ccGLBindTexture2D(m_texture);               //����������λ  
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, w, h, 0); //��ȡ��Ļ���ݵ�����  
	glEnableVertexAttribArray(m_attributePosition);  
	glDisableVertexAttribArray(m_attributeColor);  

	//����attribute����  
	GLfloat vertices[12] = {  
		0, 0, //����0
		w, 0, //����1
		w, h, //����2
		0, 0, //����0
		0, h, //����3
		w, h, //����2
	};  
	glVertexAttribPointer(m_attributePosition, 2, GL_FLOAT, GL_FALSE, 0, vertices);  
	glVertexAttrib4fv(m_attributeColor, color);  

	//����  
	glDrawArrays(GL_TRIANGLES, 0, 6);  
}