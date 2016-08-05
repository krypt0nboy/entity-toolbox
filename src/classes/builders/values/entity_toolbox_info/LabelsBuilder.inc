<?php

/**
 * Class LabelsValueBuilder
 *
 */
class LabelsValueBuilder extends ArrayValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'labels', $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $labelSingle = !empty($this->rawValueData['single']) ? $this->rawValueData['single'] : new LabelBuilderSingle($this->entityType, $this->rawData);
    $labelPlural = !empty($this->rawValueData['single']) ? $this->rawValueData['single'] : new LabelBuilderPlural($this->entityType, $this->rawData);
  }
}