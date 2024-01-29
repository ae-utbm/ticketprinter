import { MemoryRouter as Router, Routes, Route } from 'react-router-dom';

import './index.css';
import './App.css';

import TicketOptions from './TicketOptions';

function Base() {
  return (
    <main className="base">
      <div className="options">
        <h2>étiquettes</h2>
        <TicketOptions />

        <h2>sélection de l&apos;imprimante</h2>

        <div className="smalls">
          <div>
            <h2>paramètres</h2>
          </div>
          <div>
            <h2>dernières impressions</h2>
          </div>
        </div>
      </div>
      <div className="preview">
        <img src="" alt="preview" />
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
