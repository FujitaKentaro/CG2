#include "Basic.hlsli"

Texture2D<float4> tex : register(t0);  	// 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      	// 0番スロットに設定されたサンプラー



float4 main(VSOutput input) : SV_TARGET{
   float3 light = normalize(float3(1,-1,1));            // 右下奥 向きのライト
   float diffuse = saturate(dot(-light, input.normal));  // diffuseを[0、1]の範囲にclampする
   float brightness = diffuse + 0.3f;                   // 光源へのベクトルと法線ベクトルの内積
   float4 texcolor = float4(tex.Sample(smp, input.uv));
   return float4(texcolor.rgb * brightness+color,1);// RGBをそれぞれの法線のXYZ、Aを1で出力
}
