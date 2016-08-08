<?php

/**
 * Class AdminUIBuilder
 */
class AdminUIBuilder extends ContribArrayBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType) {
    parent::__construct($entityType, "admin ui");
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData = array(
      'path'             => '',
      'file'             => '',
      'controller class' => $this->toolboxInfo['classes']['ui controller'],
    );

    return $this->processedData;
  }
}