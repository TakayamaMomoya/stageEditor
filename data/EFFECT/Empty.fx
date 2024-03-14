float4x4 m_WVP : WorldViewProjection;

float4 m_LightDir = normalize(float4(.0f,1.0f,1.0f,1.0f));

float4 m_Ambient = 0.0f;

sampler tex0 : register(s0);

struct VS_OUTPUT
{
   float4 Pos   : POSITION; 
   float4 Col   : COLOR0;     
   float2 Tex   : TEXCOORD0;  
};

VS_OUTPUT m_VSVertexShader;

VS_OUTPUT VS( float4 Pos     : POSITION, 
              float4 Normal  : NORMAL,  
              float2 Tex     : TEXCOORD0 ) 
{
   VS_OUTPUT Out = (VS_OUTPUT)0;
   
   Out.Pos    = mul( Pos, m_WVP );
   
   Out.Tex    = Tex;
   
   float3 L = -normalize( m_LightDir.xyz );
   
   float3 N = normalize( Normal.xyz );

   Out.Col = max( m_Ambient, dot(N, L) );
   
   return Out;
}

//****************************************************************
//
//****************************************************************
float4 PS( VS_OUTPUT In ) : COLOR0
{  
   float4 Out = (float4)0;
   
   Out = In.Col * tex2D( tex0, In.Tex );
   
   return Out;
}

technique TShader
{
   pass P0
   {
      VertexShader = compile vs_3_0 VS();
      PixelShader  = compile ps_3_0 PS();
   }
}