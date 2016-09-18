<?php

/**
 * Class EntityGroupDependentBuilderTraits
 */
trait EntityGroupDependentBuilderTraits{
  /**
   * Extracts the info from toolbox_info.
   *
   * @return array
   */
  public function extractGroupInfoTemplateVars() {
    $flattened = $this->extractTemplateVars($this->groupInfo, '', 'group_info_');

    return $flattened;
  }
}