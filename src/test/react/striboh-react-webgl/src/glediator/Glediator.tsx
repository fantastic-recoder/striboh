import React, { useEffect, useState } from "react";

import * as THREE from "three";

import "./Glediator.css";

class RenderingCtx {
  renderer: THREE.WebGLRenderer | null = null;
  cube: THREE.Mesh | null = null;
  camera: THREE.PerspectiveCamera = new THREE.PerspectiveCamera(
    75,
    1,
    0.1,
    1000
  );
  scene: THREE.Scene = new THREE.Scene();
  canvas: HTMLElement | null = null;
  prevClientWidth: number = 0;
  prevClientHeigth: number = 0;

  init(): void {
    this.canvas = document.getElementById("id_Glediator");

    if (!this.canvas) throw new Error("Could not get Glediator");

    this.adjustAspect();

    if (this.renderer) return;

    this.renderer = new THREE.WebGLRenderer();
    this.renderer.setSize(this.canvas.clientWidth, this.canvas.clientHeight);

    this.canvas.appendChild(this.renderer.domElement);

    const geometry = new THREE.BoxGeometry();
    const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
    this.cube = new THREE.Mesh(geometry, material);
    this.scene.add(this.cube);
    this.camera.position.z = 5;
    console.log("Init ok!");
  }

  public rotateCube(): void {
    if (this.cube) {
      this.cube.rotation.x += 0.01;
      this.cube.rotation.y += 0.01;
    }
  }

  public adjustAspect() {
    if (this.canvas && this.renderer) {
      if (
        this.canvas.clientWidth !== this.prevClientWidth ||
        this.canvas.clientHeight !== this.prevClientHeigth
      ) {
        this.prevClientWidth = this.canvas.clientWidth;
        this.prevClientHeigth = this.canvas.clientHeight;
        console.log(
          "Updaring camera " +
            this.prevClientWidth +
            " " +
            this.prevClientHeigth +
            "."
        );
        this.renderer.setSize(
          this.canvas.clientWidth,
          this.canvas.clientHeight
        );
        this.camera.aspect = this.prevClientWidth / this.canvas.clientHeight;
        this.camera.updateProjectionMatrix();
      }
    }
  }
}

function Glediator() {
  const [ctx, setCtx] = useState(new RenderingCtx());

  useEffect(() => {
    ctx.init();

    function animate() {
      requestAnimationFrame(animate);
      ctx.rotateCube();
      ctx.adjustAspect();
      if (ctx.renderer) ctx.renderer.render(ctx.scene, ctx.camera);
      setCtx(ctx);
    }

    animate();
  }, [ctx]);

  console.log("Rendering");
  return <div id="id_Glediator"></div>;
}

export default Glediator;
