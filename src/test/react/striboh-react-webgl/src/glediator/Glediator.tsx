import React, { useEffect } from "react";
import "./Glediator.css"
import { initGlediator } from "./GlediatorCtx";


function Glediator() {
    useEffect(() => {
        initGlediator();
    }, []);
    return (
        <canvas id="id_Glediator" className="Glediator">
            Glediator TEXT</canvas>
    );
}

export default Glediator;