<?php

/**
 * Class LabelsValueBuilder
 *
 */
class LabelsValueBuilder extends ArrayBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'labels', $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedValueData['single'] = !empty($this->rawValueData['single']) ? $this->rawValueData['single'] : new LabelBuilderSingle($this->entityType, $this->rawData);
    $this->processedValueData['plural'] = !empty($this->rawValueData['single']) ? $this->rawValueData['single'] : new LabelBuilderPlural($this->entityType, $this->rawData);

    return $this->processedValueData;
  }
}