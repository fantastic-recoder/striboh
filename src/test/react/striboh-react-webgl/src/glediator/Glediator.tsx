import { cleanup } from "@testing-library/react";
import React, { useEffect, useState } from "react";
import * as THREE from 'three';

import "./Glediator.css"

var renderer: THREE.WebGLRenderer | null = null;
var cube: THREE.Mesh | null = null;
var camera: THREE.PerspectiveCamera;
var scene: THREE.Scene;

function animate() {
    requestAnimationFrame(animate);
    if (cube) {
        cube.rotation.x += 0.01;
        cube.rotation.y += 0.01;
    }
    if (renderer)
        renderer.render(scene, camera);
};

function initGlediator(): void {
    if (renderer)
        return;
    const aCanvas = document.getElementById('id_Glediator');
    if (!aCanvas)
        throw new Error("Could not get Glediator");
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(75, aCanvas.clientWidth / aCanvas.clientHeight, 0.1, 1000);

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(aCanvas.clientWidth, aCanvas.clientHeight);

    aCanvas.appendChild(renderer.domElement);

    const geometry = new THREE.BoxGeometry();
    const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
    cube = new THREE.Mesh(geometry, material);
    scene.add(cube);
    camera.position.z = 5;
    console.log("Init ok!");
}



function Glediator() {
    const [value, setValue] = useState(true);
    useEffect(() => {
        initGlediator();
        setValue(false);
        animate();
    }, []);

    console.log("Rendering");
    return (
        <div id="id_Glediator">
        </div>
    );
}

export default Glediator;