import { useState, ChangeEvent } from 'react';
import icon from '../../assets/icon.svg';
import Button from './Button';

import './index.css';
import './TicketOptions.css';

export default function TicketOptions() {
  const [selectedFile, setSelectedFile] = useState<File | undefined>(undefined);
  const [imageUrl, setImageUrl] = useState<string | undefined>(undefined);

  const handleFileChange = (event: ChangeEvent<HTMLInputElement>) => {
    const { files } = event.target;
    if (!files || files.length < 1) return;

    setSelectedFile(files[0]);
    setImageUrl(URL.createObjectURL(files[0]));
  };

  return (
    <div className="ticket-options">
      <div className="stylized-input">
        <input
          type="file"
          onChange={handleFileChange}
          max="1"
          accept="image/*"
        />
        <span className="button">ouvrir</span>
        <span className="filepath">{selectedFile?.name}</span>
      </div>

      <div className="options">
        <div className="ticket">
          <img src={imageUrl} alt="single ticket preview" />
        </div>
        <div className="buttons">
          <Button text="retourner horizontalement" icon={icon} />
          <Button text="retourner verticalement" icon={icon} />
          <Button text="tourner à droite de 90°" icon={icon} />
          <Button text="tourner à gauche de 90°" icon={icon} />
          <Button text="sauvegarder" disabled />
        </div>
      </div>
    </div>
  );
}
