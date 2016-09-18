<?php

/**
 * Class PermissionEntityOperationPermissionBuilder
 */
class PermissionEntityOperationPermissionBuilder extends PermissionEntityPermissionBuilder {
  use EntityOperationDependentTraits;

  /** {{@inheritdoc}} */
  protected function buildTitle() {
    return $this->processValueTemplate('%toolbox_info_labels_single% : ' . $this->operationName . ' any %toolbox_info_entity_type%.');
  }
}