import { MemoryRouter as Router, Routes, Route } from 'react-router-dom';

import './index.css';
import './App.css';

import TicketOptions from './TicketOptions';

function Base() {
  const imageUrl = undefined;

  return (
    <main className="base">
      <div className="options">
        <div className="elements">
          <div className="element">
            <h2>étiquette</h2>
            <TicketOptions />
          </div>

          <div className="element">
            <h2>sélection de l&apos;imprimante</h2>
          </div>

          <div className="element">
            <h2>paramètres</h2>
          </div>
          <div className="element">
            <h2>dernières impressions</h2>
          </div>
        </div>
      </div>
      <div className="preview">
        {imageUrl && <img src={imageUrl} alt="preview" />}
        {!imageUrl && <p>Aucune étiquette</p>}
      </div>
    </main>
  );
}

export default function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Base />} />
      </Routes>
    </Router>
  );
}
