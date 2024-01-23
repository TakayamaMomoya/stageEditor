xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 110;
 6.07794;9.16748;8.67882;,
 -6.78234;9.16748;8.67882;,
 -6.78234;1.11486;12.01433;,
 6.07794;1.11486;12.01433;,
 -6.78234;-6.93773;8.67882;,
 6.07794;-6.93773;8.67882;,
 -6.78234;-10.27323;0.62622;,
 6.07794;-10.27323;0.62622;,
 -6.78234;-6.93773;-7.42638;,
 6.07794;-6.93773;-7.42638;,
 -6.78234;1.11486;-10.76187;,
 6.07794;1.11486;-10.76187;,
 -6.78234;9.16748;-7.42638;,
 6.07794;9.16748;-7.42638;,
 -6.78234;12.50298;0.62622;,
 6.07794;12.50298;0.62622;,
 6.07794;1.11486;0.62622;,
 -6.78234;1.11486;0.62622;,
 -1.22060;2.77083;-25.89144;,
 -8.57007;-5.19686;-8.41059;,
 8.57007;-5.19686;-8.41059;,
 1.22059;2.77083;-25.89144;,
 -8.57007;-5.19686;10.86058;,
 8.57007;-5.19686;10.86058;,
 -8.57007;-5.19686;10.86058;,
 -8.57007;-18.83953;17.88370;,
 8.57007;-18.83953;17.88370;,
 8.57007;-5.19686;10.86058;,
 -8.57007;-104.54024;4.22024;,
 -8.57007;-106.84664;-1.66656;,
 8.57007;-106.84664;-1.66656;,
 8.57007;-104.54024;4.22024;,
 8.57007;-18.83953;17.88370;,
 8.57007;-24.68554;14.07446;,
 8.57007;-5.19686;10.86058;,
 8.57007;-5.19686;-8.41059;,
 1.22059;2.77083;-25.89144;,
 -1.22060;-52.47786;-8.41059;,
 -1.22060;2.77083;-25.89144;,
 1.22059;2.77083;-25.89144;,
 1.22059;-52.47786;-8.41059;,
 8.57007;-50.35532;0.40771;,
 8.57007;-48.54227;7.94020;,
 8.57007;-104.54024;4.22024;,
 8.57007;-106.84664;-1.66656;,
 -8.57007;-35.45645;18.39010;,
 -8.57007;-48.54227;7.94020;,
 8.57007;-48.54227;7.94020;,
 8.57007;-35.45645;18.39010;,
 -1.22060;2.77083;-25.89144;,
 -1.22060;-52.47786;-8.41059;,
 -8.57007;-24.68554;14.07446;,
 -8.57007;-50.35532;0.40771;,
 -8.57007;-48.54227;7.94020;,
 -8.57007;-35.45645;18.39010;,
 -8.57007;-5.19686;-8.41059;,
 -8.57007;-5.19686;10.86058;,
 -8.57007;-18.83953;17.88370;,
 8.57007;-35.45645;18.39010;,
 -8.57007;-48.54227;7.94020;,
 -8.57007;-104.54024;4.22024;,
 8.57007;-104.54024;4.22024;,
 8.57007;-48.54227;7.94020;,
 1.22059;-52.47786;-8.41059;,
 -8.57007;-104.54024;4.22024;,
 -8.57007;-106.84664;-1.66656;,
 -1.22060;-95.25068;-8.41059;,
 1.22059;-95.25068;-8.41059;,
 1.22059;-95.25068;-8.41059;,
 -1.22060;-95.25068;-8.41059;,
 1.22059;-95.25068;-8.41059;,
 -1.22060;-95.25068;-8.41059;,
 -7.31553;-62.05305;6.81023;,
 -7.31553;-47.54061;7.71029;,
 7.31885;-47.54061;7.71029;,
 7.31885;-62.05305;6.81023;,
 -7.31553;-47.54061;7.71029;,
 -7.31553;-47.17855;13.01468;,
 7.31885;-47.17855;13.01468;,
 7.31885;-47.54061;7.71029;,
 -7.31553;-47.17855;13.01468;,
 -7.31553;-62.95031;20.74224;,
 7.31885;-62.95031;20.74224;,
 7.31885;-47.17855;13.01468;,
 -7.31553;-97.52138;9.09876;,
 -7.31553;-101.30135;4.37605;,
 7.31885;-101.30135;4.37605;,
 7.31885;-97.52138;9.09876;,
 7.31885;-62.05305;6.81023;,
 7.31885;-47.54061;7.71029;,
 7.31885;-47.17855;13.01468;,
 7.31885;-62.95031;20.74224;,
 -7.31553;-62.95031;20.74224;,
 -7.31553;-47.17855;13.01468;,
 -7.31553;-47.54061;7.71029;,
 -7.31553;-62.05305;6.81023;,
 -7.31553;-74.99185;6.00775;,
 7.31885;-74.99185;6.00775;,
 7.31885;-74.99185;6.00775;,
 7.31885;-75.88910;19.93977;,
 -7.31553;-75.88910;19.93977;,
 7.31885;-75.88910;19.93977;,
 -7.31553;-75.88910;19.93977;,
 -7.31553;-74.99185;6.00775;,
 -7.31553;-101.30135;4.37605;,
 7.31885;-101.30135;4.37605;,
 7.31885;-101.30135;4.37605;,
 7.31885;-97.52138;9.09876;,
 -7.31553;-97.52138;9.09876;,
 -7.31553;-101.30135;4.37605;;
 
 68;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 3;3,16,0;,
 3;5,16,3;,
 3;7,16,5;,
 3;9,16,7;,
 3;11,16,9;,
 3;13,16,11;,
 3;15,16,13;,
 3;0,16,15;,
 3;1,17,2;,
 3;2,17,4;,
 3;4,17,6;,
 3;6,17,8;,
 3;8,17,10;,
 3;10,17,12;,
 3;12,17,14;,
 3;14,17,1;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 3;32,33,34;,
 3;33,35,34;,
 3;35,33,36;,
 4;37,38,39,40;,
 4;41,42,43,44;,
 4;45,46,47,48;,
 3;49,50,51;,
 3;50,52,51;,
 3;52,53,51;,
 3;51,53,54;,
 3;49,51,55;,
 3;55,51,56;,
 3;56,51,57;,
 4;26,25,45,48;,
 3;32,58,33;,
 3;51,54,57;,
 4;59,60,61,62;,
 3;58,42,33;,
 3;33,42,36;,
 3;42,41,36;,
 3;36,41,63;,
 4;64,53,52,65;,
 4;66,37,40,67;,
 4;68,63,41,44;,
 4;29,69,70,30;,
 4;52,50,71,65;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,72,75,97;,
 4;98,88,91,99;,
 4;81,100,101,82;,
 4;102,92,95,103;,
 4;104,96,97,105;,
 4;106,98,99,107;,
 4;100,84,87,101;,
 4;108,102,103,109;;
 
 MeshMaterialList {
  1;
  68;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\arms_01.png";
   }
  }
 }
 MeshNormals {
  46;
  0.000000;0.707107;0.707107;,
  0.000000;-0.000001;1.000000;,
  0.000000;-0.707107;0.707106;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.707107;-0.707107;,
  0.000000;-0.000001;-1.000000;,
  0.000000;0.707106;-0.707107;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.272716;-0.181866;-0.944749;,
  0.272716;-0.181866;-0.944749;,
  0.000000;0.977225;0.212206;,
  0.000000;-0.931088;0.364794;,
  0.000000;0.909938;0.414745;,
  0.000000;0.250249;0.968181;,
  0.987607;-0.100535;-0.120524;,
  0.000000;-0.316180;0.948699;,
  -0.980732;-0.045324;-0.190025;,
  0.998107;0.040709;-0.046104;,
  0.000000;-0.361708;0.932291;,
  0.419459;-0.132947;-0.897986;,
  -0.395410;0.015889;-0.918368;,
  0.936572;-0.014552;-0.350173;,
  -0.927548;0.097421;-0.360781;,
  0.000000;-0.780724;0.624876;,
  0.000000;0.061901;-0.998082;,
  0.000000;0.997679;-0.068098;,
  0.000000;-0.628945;0.777450;,
  0.000000;0.061902;-0.998082;,
  0.000000;0.195554;0.980693;,
  0.000000;0.061901;-0.998082;,
  0.000000;-0.260224;0.965548;,
  0.000000;0.457703;0.889105;,
  0.892782;-0.340417;-0.295052;,
  0.503084;-0.403733;-0.764137;,
  -0.323576;-0.495340;-0.806187;,
  0.931171;0.007064;-0.364514;,
  -0.970948;-0.072185;-0.228142;,
  -0.892783;-0.340416;-0.295052;,
  0.000000;-0.066284;0.997801;,
  0.992413;0.081377;-0.092162;,
  -0.931171;0.007064;-0.364514;,
  0.000000;-0.502742;-0.864436;,
  0.000000;0.439987;0.898004;,
  0.000000;0.061900;-0.998082;;
  68;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;14,12,12,14;,
  4;12,7,7,12;,
  4;33,15,15,33;,
  4;13,13,13,13;,
  3;8,16,8;,
  3;16,34,8;,
  3;34,16,35;,
  4;22,36,35,21;,
  4;23,19,8,37;,
  4;17,20,20,17;,
  3;38,38,18;,
  3;22,24,18;,
  3;24,9,18;,
  3;18,9,9;,
  3;36,18,39;,
  3;39,18,9;,
  3;9,18,9;,
  4;15,15,17,17;,
  3;8,8,16;,
  3;18,9,9;,
  4;20,40,40,20;,
  3;8,19,16;,
  3;16,19,41;,
  3;19,23,41;,
  3;35,23,21;,
  4;9,9,24,42;,
  4;10,22,21,11;,
  4;11,21,23,37;,
  4;43,10,11,43;,
  4;24,22,10,42;,
  4;29,26,26,29;,
  4;27,27,27,27;,
  4;44,30,30,44;,
  4;28,25,25,28;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;31,29,29,31;,
  4;8,8,8,8;,
  4;30,32,32,30;,
  4;9,9,9,9;,
  4;45,31,31,45;,
  4;8,8,8,8;,
  4;32,28,28,32;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  110;
  0.994150;0.008380;,
  0.975540;0.008380;,
  0.975540;0.005650;,
  0.994150;0.005650;,
  0.975540;0.008380;,
  0.994150;0.008380;,
  0.975540;0.014950;,
  0.994150;0.014950;,
  0.975540;0.021530;,
  0.994150;0.021530;,
  0.975540;0.024260;,
  0.994150;0.024260;,
  0.975540;0.021530;,
  0.994150;0.021530;,
  0.975540;0.014950;,
  0.994150;0.014950;,
  0.994150;0.014950;,
  0.975540;0.014950;,
  0.332160;0.698600;,
  0.307000;0.659450;,
  0.365680;0.659450;,
  0.340520;0.698600;,
  0.307000;0.616300;,
  0.365680;0.616300;,
  0.419090;0.710610;,
  0.419090;0.744460;,
  0.489750;0.744460;,
  0.489750;0.710610;,
  0.307020;0.617050;,
  0.307020;0.655330;,
  0.365150;0.655330;,
  0.365150;0.617050;,
  0.390910;0.743090;,
  0.381460;0.756970;,
  0.373490;0.710690;,
  0.325680;0.710690;,
  0.282320;0.691770;,
  0.249610;0.841580;,
  0.249610;0.701000;,
  0.261150;0.701000;,
  0.261150;0.841580;,
  0.347560;0.817920;,
  0.366240;0.813620;,
  0.357010;0.946580;,
  0.342410;0.952060;,
  0.419090;0.785700;,
  0.419090;0.818170;,
  0.489750;0.818170;,
  0.489750;0.785700;,
  0.282320;0.691770;,
  0.325680;0.822960;,
  0.381460;0.756970;,
  0.347560;0.817920;,
  0.366240;0.813620;,
  0.392170;0.782540;,
  0.325680;0.710690;,
  0.373490;0.710690;,
  0.390910;0.743090;,
  0.392170;0.782540;,
  0.419950;0.711140;,
  0.419950;0.947530;,
  0.491360;0.947530;,
  0.491360;0.711140;,
  0.325680;0.822960;,
  0.357010;0.946580;,
  0.342410;0.952060;,
  0.249610;0.950410;,
  0.261150;0.950410;,
  0.325680;0.924530;,
  0.331950;0.699200;,
  0.340220;0.699200;,
  0.325680;0.924530;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.421100;0.680420;,
  0.421100;0.617920;,
  0.483600;0.617920;,
  0.483600;0.680420;,
  0.424260;0.814790;,
  0.424260;0.853920;,
  0.484600;0.853920;,
  0.484600;0.814790;,
  0.424260;0.939710;,
  0.424260;0.949090;,
  0.484600;0.949090;,
  0.484600;0.939710;,
  0.363440;0.845700;,
  0.365670;0.811240;,
  0.378830;0.810380;,
  0.398000;0.847830;,
  0.398000;0.847830;,
  0.378830;0.810380;,
  0.365670;0.811240;,
  0.363440;0.845700;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.361450;0.876420;,
  0.396010;0.878550;,
  0.424260;0.886030;,
  0.484600;0.886030;,
  0.396010;0.878550;,
  0.361450;0.876420;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.357400;0.938890;,
  0.369120;0.929920;,
  0.369120;0.929920;,
  0.357400;0.938890;;
 }
}