<?php

/**
 * Class EntityDependentHookBuilder
 */
class EntityDependentHookBuilder extends HookBuilder {
  use EntityDependentTraits, EntityGroupDependentTraits, EntityGroupDependentBuilderTraits;

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractGroupInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /** {{@inheritdoc}} */
  protected function autoSet() {
    parent::autoSet();
    $this->autoSetGroupInfo();
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $pass = array(
      'entity_type' => $this->entityType,
      'fieldable'   => $this->fieldable,
    );
    if (isset($this->groupName)) {
      $pass += array(
        'group_name' => $this->groupName,
        'group_info' => $this->groupInfo
      );
    }
    $args = $this->mergeConstructArgs($pass, $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}