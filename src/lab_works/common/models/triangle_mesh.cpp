#include "triangle_mesh.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace M3D_ISICG
{
	TriangleMesh::TriangleMesh( const std::string &				  p_name,
								const std::vector<Vertex> &		  p_vertices,
								const std::vector<unsigned int> & p_indices,
								const Material &				  p_material ) :
		_name( p_name ),
		_vertices( p_vertices ), _indices( p_indices ), _material( p_material )
	{
		_vertices.shrink_to_fit();
		_indices.shrink_to_fit();
		_setupGL();
	}

	void TriangleMesh::render( const GLuint p_glProgram ) const
	{    
	    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glBindVertexArray(_vao );
		glDrawElements( GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );       
	    glProgramUniform3f( p_glProgram, glGetUniformLocation( p_glProgram, "ambient" ), 1.0f, .0f, 0.0f );
		glProgramUniform3f( p_glProgram, glGetUniformLocation( p_glProgram, "lightPos" ), 1.0f, 1.0f, .0f );
		glProgramUniform3f( p_glProgram, glGetUniformLocation( p_glProgram, "lightColor" ), 0.0f, 1.0f, 0.f );
		glProgramUniform3f( p_glProgram, glGetUniformLocation( p_glProgram, "objectColor" ), 0.0f, 1.0f,0.f );
		glProgramUniform1i(p_glProgram, glGetUniformLocation( p_glProgram, "uHasDiffuseMap" ), _material._hasDiffuseMap );  
		glBindTextureUnit( 1,_material._diffuseMap._id);
		
	
	}
	

	void TriangleMesh::cleanGL()
	{
		glDisableVertexArrayAttrib( _vao, 0 );
		glDisableVertexArrayAttrib( _vao, 1 );
		glDisableVertexArrayAttrib( _vao, 2 );
		glDisableVertexArrayAttrib( _vao, 3 );
		glDisableVertexArrayAttrib( _vao, 4 );
		glDeleteVertexArrays( 1, &_vao );
		glDeleteBuffers( 1, &_vbo );
		glDeleteBuffers( 1, &_ebo );     
		glBindTextureUnit( 0, _material._diffuseMap._id );
	}

	void TriangleMesh::_setupGL()
	{		
	    glCreateBuffers( 1, &_vbo);
		glNamedBufferData( _vbo, sizeof( Vertex )*_vertices.size(),_vertices.data(), GL_STATIC_DRAW );
	
		glCreateBuffers( 1, &_ebo );
		glNamedBufferData( _ebo, sizeof( unsigned int ) * _indices.size(), _indices.data(), GL_STATIC_DRAW );
		glCreateVertexArrays( 1, &_vao);
	   glVertexArrayElementBuffer( _vao, _ebo);
	  
	   //____________Enable my attributes_________________________
	   glEnableVertexArrayAttrib( _vao, 0 );
	   glEnableVertexArrayAttrib( _vao, 1);
	   glEnableVertexArrayAttrib( _vao, 2 );
	   glEnableVertexArrayAttrib( _vao, 3 );
	   glEnableVertexArrayAttrib( _vao, 4 );
	   //________Binding the vbo to be read by vao______________________
	   glVertexArrayVertexBuffer( _vao, 0, _vbo, 0, sizeof( Vertex ) ); 
		//_______________set up The format of my attributes______________
	   glVertexArrayAttribFormat( _vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, _position)); 
	   glVertexArrayAttribFormat( _vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _normal ) );
	   glVertexArrayAttribFormat( _vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof( Vertex, _texCoords ) );
	   glVertexArrayAttribFormat( _vao, 3, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _tangent ) );
	   glVertexArrayAttribFormat( _vao, 4, 3, GL_FLOAT, GL_FALSE, offsetof( Vertex, _bitangent ) );

	  //__________make all attributes read from the same buffer_______________________
	   glVertexArrayAttribBinding( _vao, 0, 0 );
	   glVertexArrayAttribBinding( _vao, 1, 0 );
	   glVertexArrayAttribBinding( _vao, 2, 0 ); 
	   glVertexArrayAttribBinding( _vao, 3, 0 );
	   glVertexArrayAttribBinding( _vao, 4, 0 );
	   


	  

	}
} // namespace M3D_ISICG
